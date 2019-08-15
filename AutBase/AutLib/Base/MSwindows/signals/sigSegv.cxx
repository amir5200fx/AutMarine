#include <sigSegv.hxx>

#include <error.hxx>
#include <OSstream.hxx>
#include <JobInfo.hxx>
#include <IOstreams.hxx>

#include <signal.h>

__p_sig_fn_t AutLib::sigSegv::oldAction_ = SIG_DFL;

void AutLib::sigSegv::sigSegvHandler(int)
{
	// Reset old handling
	const __p_sig_fn_t success = ::signal(SIGSEGV, oldAction_);

	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"AutLib::sigSegv::sigSegvHandler()"
		) << "Cannot reset SIGSEGV trapping"
			<< abort(FatalError);
	}

	// Update jobInfo file
	jobInfo.signalEnd();

	error::printStack(Perr);

	// Throw signal (to old handler)
	::raise(SIGSEGV);
}

AutLib::sigSegv::sigSegv()
{
	oldAction_ = SIG_DFL;
}

AutLib::sigSegv::~sigSegv()
{
	// Reset old handling
	const __p_sig_fn_t success = ::signal(SIGSEGV, oldAction_);
	oldAction_ = SIG_DFL;

	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"AutLib::sigSegv::~sigSegv()"
		) << "Cannot reset SIGSEGV trapping"
			<< abort(FatalError);
	}
}

void AutLib::sigSegv::set(const bool verbose)
{
	if (SIG_DFL != oldAction_)
	{
		FatalErrorIn
		(
			"AutLib::sigSegv::set()"
		) << "Cannot call sigSegv::set() more than once"
			<< abort(FatalError);
	}

	oldAction_ = ::signal(SIGSEGV, &AutLib::sigSegv::sigSegvHandler);

	if (SIG_ERR == oldAction_)
	{
		oldAction_ = SIG_DFL;

		FatalErrorIn
		(
			"AutLib::sigSegv::set()"
		) << "Cannot set SIGSEGV trapping"
			<< abort(FatalError);
	}
}