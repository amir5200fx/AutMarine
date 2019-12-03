#pragma once
#ifndef _CadAnalys_Patch_Header
#define _CadAnalys_Patch_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_Patch
		: public SurfType
	{

		/*Private Data*/

	protected:

		CadAnalys_Patch(const SurfType& theSurface)
			: SurfType(theSurface)
		{}

	public:


		typedef SurfType base;
	};
}

#endif // !_CadAnalys_Patch_Header
