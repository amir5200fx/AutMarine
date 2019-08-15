#include <Merge_Pnt.hxx>

const Standard_Real AutLib::Merge_Info::DEFAULT_RADIUS = 1.0E-6;
const Standard_Real AutLib::Merge_Info::DEFAULT_RESOLUTION = 1.0E-3;

AutLib::Merge_Info::Merge_Info()
	: theResolution_(DEFAULT_RESOLUTION)
	, theRadius_(DEFAULT_RADIUS)
{}