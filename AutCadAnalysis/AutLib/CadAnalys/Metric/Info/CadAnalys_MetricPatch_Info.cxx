#include <CadAnalys_MetricPatch_Info.hxx>

#include <CadAnalys_MetricPatch_System.hxx>

AutLib::CadAnalys_MetricPatch_Info::CadAnalys_MetricPatch_Info()
	: theMaxDet_(0)
	, theNbSegmentsU_(DEFAULT_NB_SEGMENTS_U)
	, theNbSegmentsV_(DEFAULT_NB_SEGMENTS_V)
{
	theIntgInfo_ = cadAnalysSys::normalize_metric_intg_info;
}