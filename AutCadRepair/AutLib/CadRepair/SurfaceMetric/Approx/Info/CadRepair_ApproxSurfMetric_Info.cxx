#include <CadRepair_ApproxSurfMetric_Info.hxx>

namespace AutLib
{

	const Standard_Integer CadRepair_ApproxSurfMetric_Info::MIN_LEVEL(2);
	const Standard_Integer CadRepair_ApproxSurfMetric_Info::MAX_LEVEL(5);

	const Standard_Real CadRepair_ApproxSurfMetric_Info::DEFAULT_DEGENERACY(1.0E-6);
	const Standard_Real CadRepair_ApproxSurfMetric_Info::DEFAULT_TOLERANCE(0.3);
}

AutLib::CadRepair_ApproxSurfMetric_Info::CadRepair_ApproxSurfMetric_Info()
	: theMinLevel_(MIN_LEVEL)
	, theMaxLevel_(MAX_LEVEL)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theDegeneracy_(DEFAULT_DEGENERACY)
{}