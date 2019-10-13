#include <Marine_StillWaterProfile.hxx>

#include <Geo_Interpolate.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Real 
AutLib::Marine_StillWaterProfile::Value
(
	const Standard_Real x
) const
{
	if (NOT IsInside(x))
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real x) const") << endl
			<< "Invalid Data: outside of the boundary, x = " << x << endl
			<< " - lower: " << Lower() << endl
			<< " - upper: " << Upper() << endl
			<< abort(FatalError);
	}

	return Geo_Interpolate::Linear(x, Lower(), TA()(), Upper(), TF()());
}