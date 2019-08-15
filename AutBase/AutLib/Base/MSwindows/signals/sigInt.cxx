#include <sigInt.hxx>

#include <JobInfo.hxx>
#include <error.hxx>

#include <signal.h>

__p_sig_fn_t AutLib::sigInt::oldAction_ = SIG_DFL;

void AutLib::sigInt::sigIntHandler(int)
{
	// Reset old handling
	const __p_sig_fn_t success = ::signal(SIGINT, oldAction_);

	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"AutLib::sigInt::sigIntHandler()"
		) << "Cannot reset SIGINT trapping"
			<< abort(FatalError);
	}

	// Update jobInfo file
	jobInfo.signalEnd();

	// Throw signal (to old handler)
	raise(SIGINT);
}

AutLib::sigInt::sigInt()
{
	oldAction_ = SIG_DFL;
}

AutLib::sigInt::~sigInt()
{
	// Reset old handling
	const __p_sig_fn_t success = ::signal(SIGINT, oldAction_);
	oldAction_ = SIG_DFL;

	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"AutLib::sigInt::~sigInt()"
		) << "Cannot reset SIGINT trapping"
			<< abort(FatalError);
	}
}

void AutLib::sigInt::set(const bool verbose)
{
	if (SIG_DFL != oldAction_)
	{
		FatalErrorIn
		(
			"AutLib::sigInt::set()"
		) << "Cannot call sigInt::set() more than once"
			<< abort(FatalError);
	}

	oldAction_ = ::signal(SIGINT, &AutLib::sigInt::sigIntHandler);

	if (SIG_ERR == oldAction_)
	{
		oldAction_ = SIG_DFL;

		FatalErrorIn
		(
			"AutLib::sigInt::set()"
		) << "Cannot set SIGINT trapping"
			<< abort(FatalError);
	}
}