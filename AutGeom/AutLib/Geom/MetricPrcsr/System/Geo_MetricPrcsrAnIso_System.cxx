#include <Geo_MetricPrcsrAnIso_System.hxx>

#include <Numeric_AdaptIntegrationInfo.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>

namespace AutLib
{

	std::shared_ptr<Numeric_AdaptIntegrationInfo> metricPrcsrSys::metric_processor_aniso_integration_info =
		std::make_shared<Numeric_AdaptIntegrationInfo>();

	std::shared_ptr<Geo_MetricPrcsrAnIso_Info> metricPrcsrSys::metric_processor_aniso_info =
		std::make_shared<Geo_MetricPrcsrAnIso_Info>();
}

void AutLib::metricPrcsrSys::InitRunTime()
{
	auto& intg = *metric_processor_aniso_integration_info;
	intg.SetMaxNbIterations(100);
	intg.SetNbInitIterations(2);
	intg.SetTolerance(1.0E-4);


	auto& inf = *metric_processor_aniso_info;
	inf.OverrideIntegInfo(metric_processor_aniso_integration_info);
	inf.SetNbSamples(3);
}