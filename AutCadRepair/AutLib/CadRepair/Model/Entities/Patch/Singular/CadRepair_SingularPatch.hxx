#pragma once
#ifndef _CadRepair_SingularPatch_Header
#define _CadRepair_SingularPatch_Header

#include <CadRepair_ImpPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadRepair_SingularPatch
		: public CadRepair_ImpPatch<SurfType>
	{

		/*private Data*/

	protected:

		CadRepair_SingularPatch(const std::shared_ptr<SurfType>& theSurface)
			: CadRepair_ImpPatch<SurfType>(theSurface)
		{}

	public:

		typedef CadRepair_ImpPatch<SurfType>
			base;
	};
}

#endif // !_CadRepair_SingularPatch_Header
