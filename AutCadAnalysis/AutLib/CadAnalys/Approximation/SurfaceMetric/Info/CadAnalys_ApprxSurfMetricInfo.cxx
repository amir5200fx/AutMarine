#include <CadAnalys_ApprxSurfMetricInfo.hxx>

namespace AutLib
{

	const Standard_Integer CadAnalys_ApprxSurfMetricInfo::MIN_LEVEL(2);
	const Standard_Integer CadAnalys_ApprxSurfMetricInfo::MAX_LEVEL(6);

	const Standard_Real CadAnalys_ApprxSurfMetricInfo::DEFAULT_DEGENERACY(1.0E-6);
	const Standard_Real CadAnalys_ApprxSurfMetricInfo::DEFAULT_TOLERANCE(0.3);
}

AutLib::CadAnalys_ApprxSurfMetricInfo::CadAnalys_ApprxSurfMetricInfo()
	: theMinLevel_(MIN_LEVEL)
	, theMaxLevel_(MAX_LEVEL)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theDegeneracy_(DEFAULT_DEGENERACY)
	, HasDegeneracy_(Standard_False)
	, theMaxDet_(0)
{}