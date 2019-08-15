#include <subCycleTime.hxx>

AutLib::subCycleTime::subCycleTime(Time& t, const label nSubCycles)
	: time_(t)
	, nSubCycles_(nSubCycles)
	, subCycleIndex_(0)
{
	time_.subCycle(nSubCycles_);
}

AutLib::subCycleTime::~subCycleTime()
{
	endSubCycle();
}

bool AutLib::subCycleTime::end() const
{
	return subCycleIndex_ > nSubCycles_;
}


void AutLib::subCycleTime::endSubCycle()
{
	time_.endSubCycle();
}

AutLib::subCycleTime& AutLib::subCycleTime::operator++()
{
	time_++;
	subCycleIndex_++;
	return *this;
}


AutLib::subCycleTime& AutLib::subCycleTime::operator++(int)
{
	return operator++();
}