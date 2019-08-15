#include <timer.hxx>

#include <MSwindows.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#define WINVER 0x0500 // To access CreateTimerQueueTimer
#include <windows.h>
#include <signal.h>

#define SIGALRM 14

const ::AutLib::word AutLib::timer::typeName(AutLib::timer::typeName_());
::AutLib::debug::debugSwitch AutLib::timer::debug(std::string(AutLib::timer::typeName_()), 0, "");;

jmp_buf AutLib::timer::envAlarm;

__p_sig_fn_t AutLib::timer::oldAction_ = SIG_DFL;

static HANDLE hTimer_ = NULL;

void AutLib::timer::signalHandler(int)
{
	if (debug)
	{
		Info << "AutLib::timer::signalHandler(int sig) : "
			<< " timed out. Jumping."
			<< endl;
	}
	longjmp(envAlarm, 1);
}


static VOID CALLBACK timerExpired(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	::raise(SIGALRM);
}

// Construct from components
AutLib::timer::timer(const unsigned int newTimeOut)
	:
	newTimeOut_(newTimeOut)
{

	if (newTimeOut > 0)
	{
		// Is singleton since handler is static function
		if (NULL != hTimer_)
		{
			FatalErrorIn
			(
				"AutLib::timer::timer(const unsigned int)"
			) << "timer already used."
				<< abort(FatalError);
		}

		// Install alarm signal handler:
		oldAction_ = ::signal(SIGALRM, &AutLib::timer::signalHandler);

		if (SIG_ERR == oldAction_)
		{
			oldAction_ = SIG_DFL;

			FatalErrorIn
			(
				"AutLib::timer::timer(const unsigned int)"
			) << "sigaction(SIGALRM) error"
				<< abort(FatalError);
		}

		if (debug)
		{
			Info << "AutLib::timer::timer(const unsigned int) : "
				<< " installing timeout " << int(newTimeOut_)
				<< " seconds." << endl;
		}

		const bool success =
			::CreateTimerQueueTimer(&hTimer_,
				NULL,
				(WAITORTIMERCALLBACK)timerExpired,
				NULL,
				newTimeOut * 1000,
				0, 0);

		if (!success)
		{
			hTimer_ = NULL;
			FatalErrorIn
			(
				"AutLib::timer::timer(const unsigned int)"
			) << "CreateTimerQueueTimer, "
				<< MSwindows::getLastError()
				<< abort(FatalError);
		}
	}
}

AutLib::timer::~timer()
{
	if (newTimeOut_ > 0)
	{
		// Reset timer
		const bool timerSuccess =
			::DeleteTimerQueueTimer(NULL, hTimer_, NULL);
		hTimer_ = NULL;

		if (!timerSuccess)
		{
			FatalErrorIn
			(
				"AutLib::timer::~timer() "
			) << "DeleteTimerQueueTimer, "
				<< MSwindows::getLastError()
				<< abort(FatalError);
		}

		if (debug)
		{
			Info << "AutLib::timer::~timer() timeOut="
				<< int(newTimeOut_) << endl;
		}

		const __p_sig_fn_t signalSuccess = signal(SIGALRM, oldAction_);
		oldAction_ = SIG_DFL;

		// Restore signal handler
		if (SIG_ERR == signalSuccess)
		{
			FatalErrorIn
			(
				"AutLib::timer::~timer()"
			) << "sigaction(SIGALRM) error"
				<< abort(FatalError);
		}
	}
}