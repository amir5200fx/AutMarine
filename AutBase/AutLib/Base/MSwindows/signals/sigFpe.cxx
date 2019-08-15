#include <sigFpe.hxx>

#include <error.hxx>
#include <JobInfo.hxx>
#include <OSstream.hxx>
#include <OSspecific.hxx>
#include <IOstreams.hxx>

#include <signal.h>

__p_sig_fn_t AutLib::sigFpe::oldAction_ = SIG_DFL;

static unsigned int fpOld_ = 0;


static void clearFpe()
{
	//_clearfp();
	//_controlfp(fpOld_, 0xFFFFFFFF);
}


void AutLib::sigFpe::sigFpeHandler(int)
{
	const __p_sig_fn_t success = ::signal(SIGFPE, oldAction_);

	// Reset old handling
	if (SIG_ERR == success)
	{
		FatalErrorIn
		(
			"AutLib::sigSegv::sigFpeHandler()"
		) << "Cannot reset SIGFPE trapping"
			<< abort(FatalError);
	}

	// Update jobInfo file
	jobInfo.signalEnd();

	error::printStack(Perr);

	clearFpe();

	// Throw signal (to old handler)
	::raise(SIGFPE);
}

AutLib::sigFpe::sigFpe()
{
	oldAction_ = SIG_DFL;
}

AutLib::sigFpe::~sigFpe()
{
	if (env("FOAM_SIGFPE"))
	{
		clearFpe();

		// Reset signal
		const __p_sig_fn_t success = ::signal(SIGFPE, oldAction_);
		oldAction_ = SIG_DFL;

		if (SIG_ERR == success)
		{
			FatalErrorIn
			(
				"AutLib::sigFpe::~sigFpe()"
			) << "Cannot reset SIGFPE trapping"
				<< abort(FatalError);
		}
	}

	if (env("FOAM_SETNAN"))
	{
		WarningIn("AutLib::sigFpe::~sigFpe()")
			<< "FOAM_SETNAN not supported under MSwindows "
			<< endl;
	}
}

void AutLib::sigFpe::set(const bool verbose)
{
	if (SIG_DFL != oldAction_)
	{
		FatalErrorIn
		(
			"AutLib::sigFpe::set()"
		) << "Cannot call sigFpe::set() more than once"
			<< abort(FatalError);
	}

	if (env("FOAM_SIGFPE"))
	{
		if (verbose)
		{
			Info << "SigFpe : Enabling floating point exception trapping"
				<< " (FOAM_SIGFPE)." << endl;
		}
		/*
		fpOld_ = _controlfp(0, 0);
		const unsigned int fpNew =
		fpOld_ & ~(_EM_ZERODIVIDE | _EM_INVALID | _EM_OVERFLOW);
		_controlfp(fpNew, _MCW_EM);

		oldAction_ = ::signal(SIGFPE, &AutLib::sigFpe::sigFpeHandler);

		if( SIG_ERR == oldAction_ )
		{
		oldAction_ = SIG_DFL;

		FatalErrorIn
		(
		"AutLib::sigFpe::set()"
		)   << "Cannot set SIGFPE trapping"
		<< abort(FatalError);
		}
		*/
	}


	if (env("FOAM_SETNAN"))
	{
		if (verbose)
		{
			WarningIn("AutLib::sigFpe::set()")
				<< "FOAM_SETNAN not supported under MSwindows "
				<< endl;
		}
	}
}