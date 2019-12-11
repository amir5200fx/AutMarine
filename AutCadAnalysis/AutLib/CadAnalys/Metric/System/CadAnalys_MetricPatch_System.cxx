#include <CadAnalys_MetricPatch_System.hxx>

#include <Numeric_AdaptIntegrationInfo.hxx>

namespace AutLib
{

	std::shared_ptr<Numeric_AdaptIntegrationInfo>
		cadAnalysSys::normalize_metric_intg_info = std::make_shared<Numeric_AdaptIntegrationInfo>();
}

void AutLib::cadAnalysSys::InitRunTime()
{
	auto& info = *normalize_metric_intg_info;

	info.SetNbInitIterations(6);
	info.SetTolerance(1.0e-6);
}