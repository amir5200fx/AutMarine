#pragma once
#ifndef _CadAnalys_SingularPatch_Header
#define _CadAnalys_SingularPatch_Header

#include <CadAnalys_ImpPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_SingularPatch
		: public CadAnalys_ImpPatch<SurfType>
	{

		/*Private Data*/

	protected:

		CadAnalys_SingularPatch(const SurfType& theSurface)
			: CadAnalys_ImpPatch<SurfType>(theSurface)
		{}

	public:

		typedef CadAnalys_ImpPatch<SurfType> base;
	};
}

#endif // !_CadAnalys_SingularPatch_Header
