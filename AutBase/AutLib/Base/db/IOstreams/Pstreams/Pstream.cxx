#include <Pstream.hxx>

#include <OSspecific.hxx>
#include <IOstreams.hxx>

#include <mpi.h>

#if defined(WM_SP)
#   define MPI_SCALAR MPI_FLOAT
#elif defined(WM_DP)
#   define MPI_SCALAR MPI_DOUBLE
#elif defined(WM_LDP)
#   define MPI_SCALAR MPI_LONG_DOUBLE
#endif

const ::AutLib::word AutLib::Pstream::typeName(AutLib::Pstream::typeName_());
::AutLib::debug::debugSwitch AutLib::Pstream::debug(std::string(AutLib::Pstream::typeName_()), 0, "");;

template<>
const char* AutLib::NamedEnum<AutLib::Pstream::commsTypes, 3>::names[] =
{
	"blocking",
	"scheduled",
	"nonBlocking"
};

const AutLib::NamedEnum<AutLib::Pstream::commsTypes, 3>
AutLib::Pstream::commsTypeNames;

void AutLib::Pstream::setParRun()
{
	parRun_ = true;

	Pout.prefix() = '[' + name(myProcNo()) + "] ";
	Perr.prefix() = '[' + name(myProcNo()) + "] ";
}


void AutLib::Pstream::calcLinearComm(const label nProcs)
{
	linearCommunication_.setSize(nProcs);

	// Master
	labelList belowIDs(nProcs - 1);
	for (AutLib::label i = 0; i < (belowIDs).size(); i++)
	{
		belowIDs[i] = i + 1;
	}

	linearCommunication_[0] = commsStruct
	(
		nProcs,
		0,
		-1,
		belowIDs,
		labelList(0)
	);

	// Slaves. Have no below processors, only communicate up to master
	for (label procID = 1; procID < nProcs; procID++)
	{
		linearCommunication_[procID] = commsStruct
		(
			nProcs,
			procID,
			0,
			labelList(0),
			labelList(0)
		);
	}
}


// Append my children (and my children children etc.) to allReceives.
void AutLib::Pstream::collectReceives
(
	const label procID,
	const List<dynamicLabelList >& receives,
	dynamicLabelList& allReceives
)
{
	const dynamicLabelList& myChildren = receives[procID];

	for (label childI = 0; childI < (myChildren).size(); childI++)
	{
		allReceives.append(myChildren[childI]);
		collectReceives(myChildren[childI], receives, allReceives);
	}
}


// Tree like schedule. For 8 procs:
// (level 0)
//      0 receives from 1
//      2 receives from 3
//      4 receives from 5
//      6 receives from 7
// (level 1)
//      0 receives from 2
//      4 receives from 6
// (level 2)
//      0 receives from 4
//
// The sends/receives for all levels are collected per processor (one send per
// processor; multiple receives possible) creating a table:
//
// So per processor:
// proc     receives from   sends to
// ----     -------------   --------
//  0       1,2,4           -
//  1       -               0
//  2       3               0
//  3       -               2
//  4       5               0
//  5       -               4
//  6       7               4
//  7       -               6
void AutLib::Pstream::calcTreeComm(label nProcs)
{
	label nLevels = 1;
	while ((1 << nLevels) < nProcs)
	{
		nLevels++;
	}

	List<dynamicLabelList > receives(nProcs);
	labelList sends(nProcs, -1);

	// Info<< "Using " << nLevels << " communication levels" << endl;

	label offset = 2;
	label childOffset = offset / 2;

	for (label level = 0; level < nLevels; level++)
	{
		label receiveID = 0;
		while (receiveID < nProcs)
		{
			// Determine processor that sends and we receive from
			label sendID = receiveID + childOffset;

			if (sendID < nProcs)
			{
				receives[receiveID].append(sendID);
				sends[sendID] = receiveID;
			}

			receiveID += offset;
		}

		offset <<= 1;
		childOffset <<= 1;
	}

	// For all processors find the processors it receives data from
	// (and the processors they receive data from etc.)
	List<dynamicLabelList > allReceives(nProcs);
	for (label procID = 0; procID < nProcs; procID++)
	{
		collectReceives(procID, receives, allReceives[procID]);
	}


	treeCommunication_.setSize(nProcs);

	for (label procID = 0; procID < nProcs; procID++)
	{
		treeCommunication_[procID] = commsStruct
		(
			nProcs,
			procID,
			sends[procID],
			receives[procID].shrink(),
			allReceives[procID].shrink()
		);
	}
}


// Callback from Pstream::init() : initialize linear and tree communication
// schedules now that nProcs is known.
void AutLib::Pstream::initCommunicationSchedule()
{
	calcLinearComm(nProcs());
	calcTreeComm(nProcs());
}


// NOTE:
// valid parallel options vary between implementations, but flag common ones.
// if they are not removed by MPI_Init(), the subsequent argument processing
// will notice that they are wrong
void AutLib::Pstream::addValidParOptions(HashTable<string>& validParOptions)
{
	validParOptions.insert("np", "");
	validParOptions.insert("p4pg", "PI file");
	validParOptions.insert("p4wd", "directory");
	validParOptions.insert("p4amslave", "");
	validParOptions.insert("p4yourname", "hostname");
	validParOptions.insert("GAMMANP", "number of instances");
	validParOptions.insert("machinefile", "machine file");
}


bool AutLib::Pstream::init(int& argc, char**& argv)
{
	MPI_Init(&argc, &argv);

	int numprocs;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myProcNo_);

	if (numprocs <= 1)
	{
		FatalErrorIn("Pstream::init(int& argc, char**& argv)")
			<< "bool Pstream::init(int& argc, char**& argv) : "
			"attempt to run parallel on 1 processor"
			<< AutLib::abort(FatalError);
	}

	procIDs_.setSize(numprocs);

	for (AutLib::label procNo = 0; procNo < (procIDs_).size(); procNo++)
	{
		procIDs_[procNo] = procNo;
	}

	setParRun();

#   ifndef SGIMPI
	string bufferSizeName = getEnv("MPI_BUFFER_SIZE");

	if (bufferSizeName.size())
	{
		int bufferSize = atoi(bufferSizeName.c_str());

		if (bufferSize)
		{
			MPI_Buffer_attach(new char[bufferSize], bufferSize);
		}
	}
	else
	{
		FatalErrorIn("Pstream::init(int& argc, char**& argv)")
			<< "Pstream::init(int& argc, char**& argv) : "
			<< "environment variable MPI_BUFFER_SIZE not defined"
			<< AutLib::abort(FatalError);
	}
#   endif

	int processorNameLen;
	char processorName[MPI_MAX_PROCESSOR_NAME];

	MPI_Get_processor_name(processorName, &processorNameLen);

	//signal(SIGABRT, stop);

	// Now that nprocs is known construct communication tables.
	initCommunicationSchedule();

	return true;
}


void AutLib::Pstream::exit(int errnum)
{
#   ifndef SGIMPI
	int size;
	char* buff;
	MPI_Buffer_detach(&buff, &size);
	delete[] buff;
#   endif

	if (errnum == 0)
	{
		MPI_Finalize();
		::exit(errnum);
	}
	else
	{
		MPI_Abort(MPI_COMM_WORLD, errnum);
	}
}


void AutLib::Pstream::abort()
{
	MPI_Abort(MPI_COMM_WORLD, 1);
}

// Initialise my process number to 0 (the master)
int AutLib::Pstream::myProcNo_(0);


// By default this is not a parallel run
bool AutLib::Pstream::parRun_(false);


// List of process IDs
AutLib::List<int> AutLib::Pstream::procIDs_(1, 0);


// Standard transfer message type
const int AutLib::Pstream::msgType_(1);


// Linear communication schedule
AutLib::List<AutLib::Pstream::commsStruct> AutLib::Pstream::linearCommunication_(0);


// Multi level communication schedule
AutLib::List<AutLib::Pstream::commsStruct> AutLib::Pstream::treeCommunication_(0);


// Should compact transfer be used in which floats replace doubles
// reducing the bandwidth requirement at the expense of some loss
// in accuracy
const AutLib::debug::optimisationSwitch
AutLib::Pstream::floatTransfer
(
	"floatTransfer",
	0
);


// Number of processors at which the reduce algorithm changes from linear to
// tree
const AutLib::debug::optimisationSwitch
AutLib::Pstream::nProcsSimpleSum
(
	"nProcsSimpleSum",
	16
);


AutLib::debug::optimisationSwitch
AutLib::Pstream::defaultCommsType
(
	"commsType",
	//     "nonBlocking",
	//     "scheduled",
	"blocking",
	"blocking, nonBlocking, scheduled"
);
