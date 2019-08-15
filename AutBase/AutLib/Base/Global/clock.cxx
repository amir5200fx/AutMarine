#include <clock.hxx>

#include <autString.hxx>

#include <sstream>
#include <iomanip>

const char *AutLib::clock::monthNames[] =
{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
};

time_t AutLib::clock::getTime()
{
	return ::time(reinterpret_cast<time_t*>(0));
}


const struct tm AutLib::clock::rawDate()
{
	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);
	return *timeStruct;
}


AutLib::string AutLib::clock::dateTime()
{
	std::ostringstream osBuffer;

	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);

	osBuffer
		<< std::setfill('0')
		<< std::setw(4) << timeStruct->tm_year + 1900
		<< '-' << std::setw(2) << timeStruct->tm_mon + 1
		<< '-' << std::setw(2) << timeStruct->tm_mday
		<< 'T'
		<< std::setw(2) << timeStruct->tm_hour
		<< ':' << std::setw(2) << timeStruct->tm_min
		<< ':' << std::setw(2) << timeStruct->tm_sec;

	return osBuffer.str();
}

AutLib::string AutLib::clock::date()
{
	std::ostringstream osBuffer;

	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);

	osBuffer
		<< monthNames[timeStruct->tm_mon]
		<< ' ' << std::setw(2) << std::setfill('0') << timeStruct->tm_mday
		<< ' ' << std::setw(4) << timeStruct->tm_year + 1900;

	return osBuffer.str();
}


AutLib::string AutLib::clock::clockTime()
{
	std::ostringstream osBuffer;

	time_t t = getTime();
	struct tm *timeStruct = localtime(&t);

	osBuffer
		<< std::setfill('0')
		<< std::setw(2) << timeStruct->tm_hour
		<< ':' << std::setw(2) << timeStruct->tm_min
		<< ':' << std::setw(2) << timeStruct->tm_sec;

	return osBuffer.str();
}

AutLib::clock::clock()
	: startTime_(getTime())
	, lastTime_(startTime_)
	, newTime_(startTime_)
{}

time_t AutLib::clock::elapsedClockTime() const
{
	newTime_ = getTime();
	return newTime_ - startTime_;
}


time_t AutLib::clock::clockTimeIncrement() const
{
	lastTime_ = newTime_;
	newTime_ = getTime();
	return newTime_ - lastTime_;
}