#include <CadRepair_NormalizeMetric_Info.hxx>

#include <CadRepair_NormalizeMetric_System.hxx>

const Standard_Real AutLib::CadRepair_NormalizeMetric_Info::DEFAULT_MAX_DETERMINANT(1.0E5);

const Standard_Integer AutLib::CadRepair_NormalizeMetric_Info::DEFAULT_NB_SEGMENTS_U(2);
const Standard_Integer AutLib::CadRepair_NormalizeMetric_Info::DEFAULT_NB_SEGMENTS_V(2);

AutLib::CadRepair_NormalizeMetric_Info::CadRepair_NormalizeMetric_Info()
	: theMaxDet_(DEFAULT_MAX_DETERMINANT)
	, theNbSegmentsU_(DEFAULT_NB_SEGMENTS_U)
	, theNbSegmentsV_(DEFAULT_NB_SEGMENTS_V)
	, toApply_(Standard_False)
{
	theIntgInfo_ = cadRepairSys::gl_normalize_metric_intg_info;
}