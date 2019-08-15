#include <error.hxx>

#include <dictionary.hxx>
#include <ITstream.hxx>
#include <JobInfo.hxx>
#include <Pstream.hxx>
#include <IOstreams.hxx>
#include <OStringStream.hxx>

AutLib::IOerror::IOerror(const string& title)
	: error(title)
	, ioFileName_("unknown")
	, ioStartLineNumber_(-1)
	, ioEndLineNumber_(-1)
{}

AutLib::IOerror::IOerror(const dictionary& errDict)
	: error(errDict)
	, ioFileName_(errDict.lookup("ioFileName"))
	, ioStartLineNumber_(readLabel(errDict.lookup("ioStartLineNumber")))
	, ioEndLineNumber_(readLabel(errDict.lookup("ioEndLineNumber")))
{}

AutLib::IOerror::~IOerror() throw()
{}

AutLib::OSstream& AutLib::IOerror::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const string& ioFileName,
	const label ioStartLineNumber,
	const label ioEndLineNumber
	)
{
	error::operator()(functionName, sourceFileName, sourceFileLineNumber);
	ioFileName_ = ioFileName;
	ioStartLineNumber_ = ioStartLineNumber;
	ioEndLineNumber_ = ioEndLineNumber;

	return operator OSstream&();
}


AutLib::OSstream& AutLib::IOerror::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const IOstream& ioStream
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			ioStream.name(),
			ioStream.lineNumber(),
			-1
			);
}


AutLib::OSstream& AutLib::IOerror::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const dictionary& dict
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			dict.name(),
			dict.startLineNumber(),
			dict.endLineNumber()
			);
}

namespace AutLib
{
	IOerror::operator dictionary() const
	{
		dictionary errDict(error::operator dictionary());

		errDict.remove("type");
		errDict.add("type", word("AutLib::IOerror"));

		errDict.add("ioFileName", ioFileName());
		errDict.add("ioStartLineNumber", ioStartLineNumber());
		errDict.add("ioEndLineNumber", ioEndLineNumber());

		return errDict;
	}
}

void AutLib::IOerror::exit(const int)
{
	if (!throwExceptions_ && JobInfo::constructed)
	{
		jobInfo.add("FatalIOError", operator dictionary());
		jobInfo.exit();
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
			<< "\nAUT parallel run exiting\n" << endl;
		PAUSE;
		Pstream::exit(1);
	}
	else
	{
		if (throwExceptions_)
		{
			// Make a copy of the error to throw
			IOerror errorException(*this);

			// Rewind the message buffer for the next error message
			messageStreamPtr_->rewind();

			throw errorException;
		}
		else
		{
			Perr << endl << *this << endl
				<< "\nAUT exiting\n" << endl;
			PAUSE;
			::exit(1);
		}
	}
}


void AutLib::IOerror::abort()
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
			IOerror errorException(*this);

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
	Ostream& operator<<(Ostream& os, const IOerror& ioErr)
	{
		os << endl
			<< ioErr.title().c_str() << endl
			<< ioErr.message().c_str() << endl << endl;

		os << "file: " << ioErr.ioFileName().c_str();

		if (ioErr.ioStartLineNumber() >= 0 && ioErr.ioEndLineNumber() >= 0)
		{
			os << " from line " << ioErr.ioStartLineNumber()
				<< " to line " << ioErr.ioEndLineNumber() << '.';
		}
		else if (ioErr.ioStartLineNumber() >= 0)
		{
			os << " at line " << ioErr.ioStartLineNumber() << '.';
		}

		if (IOerror::level >= 2 && ioErr.sourceFileLineNumber())
		{
			os << endl << endl
				<< "    From function " << ioErr.functionName().c_str() << endl
				<< "    in file " << ioErr.sourceFileName().c_str()
				<< " at line " << ioErr.sourceFileLineNumber() << '.';
		}

		return os;
	}
}

AutLib::IOerror AutLib::FatalIOError("--> AUT FATAL IO ERROR: ");
