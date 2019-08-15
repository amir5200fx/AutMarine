#include <profilingStack.hxx>

#include <profilingInfo.hxx>
#include <clockTime.hxx>

AutLib::profilingStack::profilingStack()
	: LIFOStack<profilingInfo*>()
{}

AutLib::profilingStack::~profilingStack()
{}

AutLib::profilingInfo &AutLib::profilingStack::top() const
{
	return *LIFOStack<profilingInfo*>::top();
}

AutLib::profilingInfo &AutLib::profilingStack::bottom() const
{
	return *LIFOStack<profilingInfo*>::bottom();
}

bool AutLib::profilingStack::empty() const
{
	return LIFOStack<profilingInfo*>::empty();
}

void AutLib::profilingStack::push(profilingInfo &a)
{
	LIFOStack<profilingInfo*>::push(&a);
	top().addedToStack();
}

AutLib::profilingInfo &AutLib::profilingStack::pop()
{
	top().removedFromStack();
	return *LIFOStack<profilingInfo*>::pop();
}

void AutLib::profilingStack::writeStackContents(Ostream &os) const
{
	if (empty())
	{
		return;
	}
	const_iterator it = begin();
	scalar oldElapsed = 0;
	do
	{
		const profilingInfo &info = *(*it);
		scalar elapsed = timers_[info.id()]->elapsedTime();

		info.writeWithOffset(os, true, elapsed, oldElapsed);

		oldElapsed = elapsed;
		++it;
	} while (it != end());
}

void AutLib::profilingStack::addTimer(const profilingInfo &info, clockTime &timer)
{
	timers_.insert(info.id(), &timer);
}