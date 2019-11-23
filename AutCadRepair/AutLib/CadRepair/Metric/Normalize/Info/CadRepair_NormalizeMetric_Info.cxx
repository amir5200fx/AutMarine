#include <CadRepair_NormalizeMetric_Info.hxx>

#include <CadRepair_NormalizeMetric_System.hxx>

AutLib::CadRepair_NormalizeMetric_Info::CadRepair_NormalizeMetric_Info()
	: theMaxDet_(0)
	, theNbSegmentsU_(DEFAULT_NB_SEGMENTS_U)
	, theNbSegmentsV_(DEFAULT_NB_SEGMENTS_V)
{
	theIntgInfo_ = cadRepairSys::normalize_metric_intg_info;
}