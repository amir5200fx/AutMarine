#pragma once
#ifndef _CadAnalys_RegularPatch_Header
#define _CadAnalys_RegularPatch_Header

#include <CadAnalys_Patch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_RegularPatch
		: public CadAnalys_Patch<SurfType>
	{

		/*Private Data*/

	public:

		typedef CadAnalys_Patch<SurfType> base;

		CadAnalys_RegularPatch(const std::shared_ptr<SurfType>& theSurface)
			: CadAnalys_Patch<SurfType>(theSurface)
		{}
	};
}

#endif // !_CadAnalys_RegularPatch_Header
