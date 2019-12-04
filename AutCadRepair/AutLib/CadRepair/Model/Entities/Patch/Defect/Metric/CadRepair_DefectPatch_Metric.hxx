#pragma once
#ifndef _CadRepair_DefectPatch_Metric_Header
#define _CadRepair_DefectPatch_Metric_Header

#include <CadRepair_DefectPatch.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadRepair_ApproxSurfMetric;

	template<class SurfType>
	class CadRepair_DefectPatch_Metric
		: public CadRepair_DefectPatch<SurfType>
	{

		/*Private Data*/

		std::shared_ptr<CadRepair_ApproxSurfMetric> theApprox_;

	public:

		typedef CadRepair_DefectPatch<SurfType>
			base;

		CadRepair_DefectPatch_Metric
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SurfType>& theSurface,
			const std::shared_ptr<CadRepair_ApproxSurfMetric>& theApprox
		)
			: CadRepair_DefectPatch<SurfType>(theIndex, theSurface)
			, theApprox_(theApprox)
		{}


		const std::shared_ptr<CadRepair_ApproxSurfMetric>& MetricApprox() const
		{
			return theApprox_;
		}
	};
}

#endif // !_CadRepair_DefectPatch_Metric_Header
