#include <sigQuit.hxx>

#include <error.hxx>
#include <JobInfo.hxx>
#include <IOstreams.hxx>

#include <signal.h>

__p_sig_fn_t AutLib::sigQuit::oldAction_ = SIG_DFL;

void AutLib::sigQuit::sigQuitHandler(int)
{
	// Reset old handling
	const __p_sig_fn_t success = ::signal(SIGBREAK, oldAction_);

	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"AutLib::sigQuit::sigQuitHandler()"
		) << "Cannot reset SIGQUIT trapping"
			<< abort(FatalError);
	}
	// Update jobInfo file
	jobInfo.signalEnd();

	error::printStack(Perr);

	// Throw signal (to old handler)
	::raise(SIGBREAK);
}

AutLib::sigQuit::sigQuit()
{
	oldAction_ = SIG_DFL;
}

AutLib::sigQuit::~sigQuit()
{
	// Reset old handling
	if (SIG_DFL != oldAction_)
	{
		const __p_sig_fn_t success = ::signal(SIGBREAK, oldAction_);
		oldAction_ = SIG_DFL;

		if (SIG_ERR == success)
		{
			FatalErrorIn("AutLib::sigQuit::~sigQuit()")
				<< "Cannot reset SIGBREAK trapping"
				<< abort(FatalError);
		}
	}
}

void AutLib::sigQuit::set(const bool verbose)
{
	if (SIG_DFL != oldAction_)
	{
		FatalErrorIn
		(
			"AutLib::sigQuit::set()"
		) << "Cannot call sigQuit::set() more than once"
			<< abort(FatalError);
	}

	oldAction_ = ::signal(SIGBREAK, &AutLib::sigQuit::sigQuitHandler);

	if (SIG_ERR == oldAction_)
	{
		oldAction_ = SIG_DFL;

		FatalErrorIn
		(
			"AutLib::sigQuit::set()"
		) << "Cannot set SIGQUIT trapping"
			<< abort(FatalError);
	}
}