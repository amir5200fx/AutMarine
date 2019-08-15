#include <TimeState.hxx>

#include <autTime.hxx>

AutLib::TimeState::TimeState()
	: dimensionedScalar(Time::timeName(0), dimTime, 0)
	, timeIndex_(0)
	, deltaT_(0)
	, deltaTSave_(0)
	, deltaT0_(0)
	, deltaTchanged_(false)
	, outputTimeIndex_(0)
	, outputTime_(false)
{}

AutLib::TimeState::~TimeState()
{}

AutLib::scalar AutLib::TimeState::userTimeToTime(const scalar theta) const
{
	return theta;
}


AutLib::scalar AutLib::TimeState::timeToUserTime(const scalar t) const
{
	return t;
}


AutLib::scalar AutLib::TimeState::timeOutputValue() const
{
	return timeToUserTime(value());
}


AutLib::label AutLib::TimeState::timeIndex() const
{
	return timeIndex_;
}


AutLib::dimensionedScalar AutLib::TimeState::deltaT() const
{
	return dimensionedScalar("deltaT", dimTime, deltaT_);
}


AutLib::dimensionedScalar AutLib::TimeState::deltaT0() const
{
	return dimensionedScalar("deltaT0", dimTime, deltaT0_);
}


bool AutLib::TimeState::outputTime() const
{
	return outputTime_;
}