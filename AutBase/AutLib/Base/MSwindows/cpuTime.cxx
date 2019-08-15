#include <cpuTime.hxx>

namespace AutLib
{

	void cpuTime::getTime(std::clock_t& t)
	{
		t = std::clock();
	}


	double cpuTime::timeDifference
	(
		const std::clock_t& start,
		const std::clock_t& end
	)
	{
		const double difference = std::difftime(end, start) / CLOCKS_PER_SEC;
		return difference;
	}

	cpuTime::cpuTime()
	{
		getTime(startTime_);
		lastTime_ = startTime_;
		newTime_ = startTime_;
	}

	double cpuTime::elapsedCpuTime() const
	{
		getTime(newTime_);
		return timeDifference(startTime_, newTime_);
	}


	double cpuTime::cpuTimeIncrement() const
	{
		lastTime_ = newTime_;
		getTime(newTime_);
		return timeDifference(lastTime_, newTime_);
	}
}