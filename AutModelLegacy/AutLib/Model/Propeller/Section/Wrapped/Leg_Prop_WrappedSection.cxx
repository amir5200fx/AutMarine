#include <Leg_Prop_WrappedSection.hxx>

AutLib::Leg_Prop_WrappedSection::Leg_Prop_WrappedSection(const Standard_Integer theSize)
{
	theFace_.resize(theSize);
	theBack_.resize(theSize);
}