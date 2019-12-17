#include <CadAnalys_Model_System.hxx>

#include <CadAnalys_Model_Info.hxx>
#include <CadRepair_ApproxSurfMetric_System.hxx>
#include <CadRepair_NormalizeMetric_System.hxx>
#include <CadRepair_ParaPlaneAR_System.hxx>
#include <CadSingularity_Detection_System.hxx>

std::shared_ptr<AutLib::CadAnalys_Model_Info> AutLib::cadAnalysSys::gl_model_analysis_info = 
std::make_shared<AutLib::CadAnalys_Model_Info>();

void AutLib::cadAnalysSys::init_model_analysis_info()
{
	auto info = *gl_model_analysis_info;
	
	info.OverrideGlobalMetricApproximation(cadRepairSys::gl_surface_metric_approximate_info);
	info.OverrideGlobalNormalizeMetric(cadRepairSys::gl_normalize_metric_info);
	info.OverrideGlobalParaPlaneAR(cadRepairSys::gl_para_plane_ar_info);
	info.OverrideGlobalSingularityDetection(cadSingularSys::gl_singularity_detection_info);
}