#pragma once
#ifndef _CadAnalys_DefectPatch_Header
#define _CadAnalys_DefectPatch_Header

#include <CadAnalys_ImpPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_DefectPatch
		: public CadAnalys_ImpPatch<SurfType>
	{

		/*Private Data*/

	protected:

		CadAnalys_DefectPatch(const std::shared_ptr<SurfType>& theSurface)
			: CadAnalys_ImpPatch<SurfType>(theSurface)
		{}

	public:

		typedef CadAnalys_ImpPatch<SurfType>
			base;


	};
}

#endif // !_CadAnalys_DefectPatch_Header
