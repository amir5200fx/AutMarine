#pragma once
#ifndef _CadAnalys_BadMetricPatch_Header
#define _CadAnalys_BadMetricPatch_Header

#include <CadAnalys_DefectPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_BadMetricPatch
		: public CadAnalys_DefectPatch<SurfType>
	{

		/*Private Data*/

	public:

		typedef CadAnalys_DefectPatch<SurfType> base;

		CadAnalys_BadMetricPatch(const SurfType& theSurface)
			: CadAnalys_DefectPatch<SurfType>(theSurface)
		{}
	};
}

#endif // !_CadAnalys_BadMetricPatch_Header
