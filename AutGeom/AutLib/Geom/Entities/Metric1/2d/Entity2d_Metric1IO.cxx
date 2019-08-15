#include <Entity2d_Metric1.hxx>

void AutLib::Entity2d_Metric1::Print(Standard_OStream & Ostream) const
{
	Ostream << " A = " << theA_ << ", B = " << theB_ << ", C = " << theC_;
}