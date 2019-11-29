#include <MeshAnalysis_Model_Info.hxx>

namespace AutLib
{
	const Standard_Real MeshAnalysis_Model_Info::DEFAULT_MIN_SIZE(0.01);
	const Standard_Real MeshAnalysis_Model_Info::DEFAULT_OPENWIRE_TOLERANCE(1.0E-4);
	const Standard_Real MeshAnalysis_Model_Info::DEFAULT_INTERECT_WIRE_TOLERANCE(1.0E-4);
}

AutLib::MeshAnalysis_Model_Info::MeshAnalysis_Model_Info()
	: theMinSize_(DEFAULT_MIN_SIZE)
	, theOpenWireTolerance_(DEFAULT_OPENWIRE_TOLERANCE)
	, theInterstWireTolerance_(DEFAULT_INTERECT_WIRE_TOLERANCE)
	, OverrideMetricApprox_(Standard_False)
	, OverrideSingDetect_(Standard_False)
{}

void AutLib::MeshAnalysis_Model_Info::OverrideMetricApproxInfo
(
	const Standard_Integer theIndex,
	const std::shared_ptr<metricApprxInfo>& theInfo
)
{
	theMetricApprxInfo_.insert(std::make_pair(theIndex, theInfo));
}

void AutLib::MeshAnalysis_Model_Info::OverrideSingDetectInfo
(
	const Standard_Integer theIndex,
	const std::shared_ptr<singularInfo>& theInfo
)
{
	theSinularDetectInfo_.insert(std::make_pair(theIndex, theInfo));
}