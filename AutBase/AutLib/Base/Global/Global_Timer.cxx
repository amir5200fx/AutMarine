#include <Global_Timer.hxx>

#include <Global_Macros.hxx>

float AutLib::global_time_duration(0);

void AutLib::Global_Timer::EstimateDuration()
{
	theEnd_ = std::chrono::high_resolution_clock::now();

	theDuration_ = theEnd_ - theStart_;

	if (theInfo_ IS_EQUAL Global_TimerInfo_ms)
	{
		global_time_duration = theDuration_.count()*1000.0f;
	}
	else if (theInfo_ IS_EQUAL Global_TimerInfo_hour)
	{
		global_time_duration = theDuration_.count() / 3600.0f;
	}
	else
	{
		global_time_duration = theDuration_.count();
	}
}

AutLib::Global_Timer::Global_Timer()
	: theInfo_(Global_TimerInfo_ms)
{
	theStart_ = std::chrono::high_resolution_clock::now();
}

AutLib::Global_Timer::~Global_Timer()
{
	EstimateDuration();
}