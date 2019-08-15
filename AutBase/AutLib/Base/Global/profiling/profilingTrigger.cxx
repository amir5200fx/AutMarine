#include <profilingTrigger.hxx>

#include <profilingPool.hxx>
#include <profilingInfo.hxx>

AutLib::profilingTrigger::profilingTrigger(const string &name)
	: clock_()
	, info_(profilingPool::getInfo(name))
	, running_(true)
{
	profilingPool::rememberTimer(info(), clock());
}

AutLib::profilingTrigger::~profilingTrigger()
{
	stop();
}

void AutLib::profilingTrigger::stop()
{
	if (running_)
	{
		scalar elapsed = clock_.elapsedTime();
		info_.update(elapsed);
		profilingPool::remove(info_);
		running_ = false;
	}
}