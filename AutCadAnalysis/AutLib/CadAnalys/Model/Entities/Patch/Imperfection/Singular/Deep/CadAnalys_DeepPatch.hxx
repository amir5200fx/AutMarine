#pragma once
#ifndef _CadAnalys_DeepPatch_Header
#define _CadAnalys_DeepPatch_Header

#include <CadAnalys_SingularPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_DeepPatch
		: public CadAnalys_SingularPatch<SurfType>
	{

		/*Private Data*/

	public:

		typedef CadAnalys_SingularPatch<SurfType> base;

		CadAnalys_DeepPatch(const std::shared_ptr<SurfType>& theSurface)
			: CadAnalys_SingularPatch<SurfType>(theSurface)
		{}
	};
}

#endif // !_CadAnalys_DeepPatch_Header
