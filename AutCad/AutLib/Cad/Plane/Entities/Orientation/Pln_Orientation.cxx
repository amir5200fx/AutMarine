#include <Pln_Orientation.hxx>

#include <Global_Macros.hxx>
AutLib::Pln_Orientation
AutLib::Reverse
(
	const Pln_Orientation theOrient
)
{
	if (theOrient IS_EQUAL Pln_Orientation_Unknown) return Pln_Orientation_Unknown;
	if (theOrient IS_EQUAL Pln_Orientation_CCW) return Pln_Orientation_CW;
	if (theOrient IS_EQUAL Pln_Orientation_CW) return Pln_Orientation_CCW;
	return Pln_Orientation_Unknown; // prevent compiler warning
}