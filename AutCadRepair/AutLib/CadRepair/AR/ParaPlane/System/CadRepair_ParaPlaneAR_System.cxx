#include <CadRepair_ParaPlaneAR_System.hxx>

#include <CadRepair_ParaPlaneAR_Info.hxx>

#include <OSspecific.hxx>
#include <OStringStream.hxx>
#include <IOstreams.hxx>
#include <dictionary.hxx>
#include <ITstream.hxx>
#include <Pstream.hxx>
#include <JobInfo.hxx>

std::shared_ptr<AutLib::CadRepair_ParaPlaneAR_Info> 
AutLib::cadRepairSys::gl_para_plane_ar_info = std::make_shared<AutLib::CadRepair_ParaPlaneAR_Info>();

AutLib::OSstream & AutLib::AR_ParaPlane_Failure::operator()
(
	const char * functionName,
	const char * sourceFileName,
	const int sourceFileLineNumber,
	const Standard_Integer theIndex,
	const word & theName
	)
{
	functionName_ = functionName;
	sourceFileName_ = sourceFileName;
	sourceFileLineNumber_ = sourceFileLineNumber;

	theIndex_ = theIndex;
	theName_ = theName;

	return operator OSstream&();
}

void AutLib::AR_ParaPlane_Failure::exit(const int errNo)
{
	if (!throwExceptions_ && JobInfo::constructed)
	{
		jobInfo.add("FatalError", operator dictionary());
		jobInfo.exit();
	}

	if (abort_)
	{
		Perr << endl << *this << endl
			<< "\nAUT aborting (AUT_ABORT set)\n" << endl;

		abort();
	}

	if (Pstream::parRun())
	{
		Perr << endl << *this << endl
			<< "\nAUT parallel run exiting\n" << endl;
		Pstream::exit(errNo);
	}
	else
	{

		if (throwExceptions_)
		{
			// Make a copy of the error to throw
			AR_ParaPlane_Failure errorException(*this);

			// Rewind the message buffer for the next error message
			messageStreamPtr_->rewind();

			throw errorException;
		}
		else
		{
			Perr << endl << *this << endl
				<< "\nAUT exiting\n" << endl;
			::exit(1);
		}
	}
}

void AutLib::AR_ParaPlane_Failure::abort()
{
	if (!throwExceptions_ && JobInfo::constructed)
	{
		jobInfo.add("FatalIOError", operator dictionary());
		jobInfo.abort();
	}

	if (abort_)
	{
		Perr << endl << *this << endl
			<< "\nAUT aborting (AUT_ABORT set)\n" << endl;
		printStack(Perr);
		::abort();
	}

	if (Pstream::parRun())
	{
		Perr << endl << *this << endl
			<< "\nAUT parallel run aborting\n" << endl;
		printStack(Perr);
		Pstream::abort();
	}
	else
	{

		if (throwExceptions_)
		{

			// Make a copy of the error to throw
			AR_ParaPlane_Failure errorException(*this);

			// Rewind the message buffer for the next error message
			messageStreamPtr_->rewind();

			throw errorException;
		}
		else
		{
			Perr << endl << *this << endl
				<< "\nAUT aborting\n" << endl;
			printStack(Perr);
			::abort();
		}
	}
}

namespace AutLib
{

	Ostream & operator<<(Ostream & os, const AR_ParaPlane_Failure & fErr)
	{
		os << endl
			<< fErr.title().c_str() << endl
			<< fErr.message().c_str();

		os << "surface's index: " << fErr.Index() << endl;
		os << "surface's name: " << fErr.Name() << endl;

		if (error::level >= 2 && fErr.sourceFileLineNumber())
		{
			os << endl << endl
				<< "    From function " << fErr.functionName().c_str() << endl
				<< "    in file " << fErr.sourceFileName().c_str()
				<< " at line " << fErr.sourceFileLineNumber() << '.';
		}

		return os;
	}
}