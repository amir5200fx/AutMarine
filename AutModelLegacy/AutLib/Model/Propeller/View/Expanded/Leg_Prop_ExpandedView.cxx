#include <Leg_Prop_ExpandedView.hxx>

void AutLib::Leg_Prop_ExpandedView::AllocateMemory
(
	const Standard_Integer theSize
)
{
	theTb_.resize(theSize);
	theTf_.resize(theSize);
	theX_.resize(theSize);
	theXs_.reserve(theSize);
	theYb_.resize(theSize);
	theYf_.resize(theSize);
}

AutLib::Leg_Prop_ExpandedView::Leg_Prop_ExpandedView
(
	const Standard_Integer theSize
)
{
	AllocateMemory(theSize);
}