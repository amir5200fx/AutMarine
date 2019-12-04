#pragma once
#ifndef _CadAnalys_Patch_Header
#define _CadAnalys_Patch_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_Patch
	{

		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;

	protected:

		CadAnalys_Patch(const std::shared_ptr<SurfType>& theSurface)
			: theSurface_(theSurface)
		{}

	public:


		typedef SurfType base;

		const std::shared_ptr<SurfType>& Surface() const
		{
			return theSurface_;
		}

	};
}

#endif // !_CadAnalys_Patch_Header
