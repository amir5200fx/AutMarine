#include <NonConvergency_Iteration_Failure.hxx>

#include <OSspecific.hxx>
#include <OStringStream.hxx>
#include <IOstreams.hxx>
#include <dictionary.hxx>
#include <ITstream.hxx>
#include <Pstream.hxx>
#include <JobInfo.hxx>

AutLib::OSstream & AutLib::NonConvergency_Iteration_Failure::operator()
(
	const char * functionName,
	const char * sourceFileName, 
	const int sourceFileLineNumber,
	const label nbIterations
	)
{
	functionName_ = functionName;
	sourceFileName_ = sourceFileName;
	sourceFileLineNumber_ = sourceFileLineNumber;

	nbIterations_ = nbIterations_;

	return operator OSstream&();
}

void AutLib::NonConvergency_Iteration_Failure::exit(const int errNo)
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
			NonConvergency_Iteration_Failure errorException(*this);

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

void AutLib::NonConvergency_Iteration_Failure::abort()
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
			NonConvergency_Iteration_Failure errorException(*this);

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
	Ostream & operator<<(Ostream & os, const NonConvergency_Iteration_Failure & fErr)
	{
		os << endl
			<< fErr.title().c_str() << endl
			<< fErr.message().c_str();

		os << "nb of Iterations: " << fErr.NbIterations() << endl;

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

AutLib::NonConvergency_Iteration_Failure AutLib::IterFail("--> AUT ITERATION FAILED: ");