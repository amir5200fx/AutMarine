#pragma once
#ifndef _Geo_MetricPrcsrAnIso_System_Header
#define _Geo_MetricPrcsrAnIso_System_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Geo_MetricPrcsrAnIso_Info;
	class Numeric_AdaptIntegrationInfo;

	namespace metricPrcsrSys
	{

		extern std::shared_ptr<Numeric_AdaptIntegrationInfo> metric_processor_aniso_integration_info;
		extern std::shared_ptr<Geo_MetricPrcsrAnIso_Info> metric_processor_aniso_info;

		void InitRunTime();
	}
}

#endif // !_Geo_MetricPrcsrAnIso_System_Header
