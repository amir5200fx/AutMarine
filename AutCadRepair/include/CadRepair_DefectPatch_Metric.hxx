#pragma once
#ifndef _CadRepair_DefectPatch_Metric_Header
#define _CadRepair_DefectPatch_Metric_Header

#include <CadRepair_DefectPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadRepair_DefectPatch_Metric
		: public CadRepair_DefectPatch<SurfType>
	{

		/*Private Data*/

	public:

		typedef CadRepair_DefectPatch<SurfType>
			base;

		CadRepair_DefectPatch_Metric
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SurfType>& theSurface
		)
			: CadRepair_DefectPatch<SurfType>(theIndex, theSurface)
		{}
	};
}

#endif // !_CadRepair_DefectPatch_Metric_Header
