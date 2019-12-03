#pragma once
#ifndef _CadAnalys_ImpPatch_Header
#define _CadAnalys_ImpPatch_Header

#include <CadAnalys_Patch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_ImpPatch
		: public CadAnaly..s_Patch<SurfType>
	{

		/*Private Data*/

	protected:

		CadAnalys_ImpPatch(const SurfType& theSurface)
			: CadAnalys_Patch<SurfType>(theSurface)
		{}

	public:

		typedef CadAnalys_Patch<SurfType> base;

	};
}

#endif // !_CadAnalys_ImpPatch_Header
