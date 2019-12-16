#include <Aft2d_MetricPrcsrAnIso_System.hxx>

#include <Numeric_AdaptIntegrationInfo.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>

namespace AutLib
{

	std::shared_ptr<Numeric_AdaptIntegrationInfo> metricSys::gl_metric_prcsr_aniso_intg_info =
		std::make_shared<Numeric_AdaptIntegrationInfo>();

	std::shared_ptr<Aft_MetricPrcsrAnIso_Info> metricSys::gl_aft_metric_prcsr_aniso_info =
		std::make_shared<Aft_MetricPrcsrAnIso_Info>();
}

void AutLib::metricSys::init_aft_metric_prcsr_aniso_info()
{
	auto& info = *gl_aft_metric_prcsr_aniso_info;
	info.OverrideIntegInfo(gl_metric_prcsr_aniso_intg_info);
}