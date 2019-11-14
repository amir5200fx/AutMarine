#include <Leg_Prop_PropView.hxx>

void AutLib::Leg_Prop_PropView::AllocateMemory(const Standard_Integer theSize)
{
	theExpanded_.resize(theSize);
	theUnWrapped_.resize(theSize);
	theWrapped_.resize(theSize);
}