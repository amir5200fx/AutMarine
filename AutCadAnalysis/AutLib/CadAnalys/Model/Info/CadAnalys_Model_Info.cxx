#include <CadAnalys_Model_Info.hxx>

namespace AutLib
{

	const Standard_Real CadAnalys_Model_Info::DEFAULT_MIN_SIZE(1.0E-3);
	const Standard_Real CadAnalys_Model_Info::DEFAULT_INTERSECT_WIRE_TOLERANCE(1.0E-3);
	const Standard_Real CadAnalys_Model_Info::DEFAULT_OPEN_WIRE_TOLERANCE(1.0E-3);
}

AutLib::CadAnalys_Model_Info::CadAnalys_Model_Info()
	: theMinSize_(DEFAULT_MIN_SIZE)
	, theOpenWireTolerance_(DEFAULT_OPEN_WIRE_TOLERANCE)
	, theIntersectWireTolerance_(DEFAULT_INTERSECT_WIRE_TOLERANCE)
	, OverrideMetricApproximation_(Standard_False)
	, OverrideNormalizeMetric_(Standard_False)
	, OverrideParaPlaneAR_(Standard_False)
	, OverrideSingularityDetection_(Standard_False)
{
}

void AutLib::CadAnalys_Model_Info::OverrideMetricApproximation
(
	const Standard_Integer theIndex,
	const std::shared_ptr<metricApproxInfo>& theInfo
)
{
	theMetricApproximation_.insert(std::make_pair(theIndex, theInfo));
}

void AutLib::CadAnalys_Model_Info::OverrideSingularityDetection
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<singlDetectInfo>& theInfo
)
{
	theSingularityDetection_.insert(std::make_pair(theIndex, theInfo));
}

void AutLib::CadAnalys_Model_Info::OverrideNormalizeMetric
(
	const Standard_Integer theIndex,
	const std::shared_ptr<normInfo>& theInfo
)
{
	theNormalizeMetric_.insert(std::make_pair(theIndex, theInfo));
}

void AutLib::CadAnalys_Model_Info::OverrideParaPlaneAR
(
	const Standard_Integer theIndex,
	const std::shared_ptr<planeArInfo>& theInfo
)
{
	theParaPlaneAR_.insert(std::make_pair(theIndex, theInfo));
}