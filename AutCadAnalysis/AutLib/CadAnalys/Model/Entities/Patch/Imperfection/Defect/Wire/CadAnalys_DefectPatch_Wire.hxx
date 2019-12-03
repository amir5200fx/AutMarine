#pragma once
#ifndef _CadAnalys_DefectPatch_Wire_Header
#define _CadAnalys_DefectPatch_Wire_Header

#include <CadAnalys_DefectPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_DefectPatch_Wire
		: public CadAnalys_DefectPatch<SurfType>
	{

		/*Private Data*/

	protected:

		CadAnalys_DefectPatch_Wire(const SurfType& theSurface)
			: CadAnalys_DefectPatch<SurfType>(theSurface)
		{}

	public:

		typedef CadAnalys_DefectPatch<SurfType>
			base;
	};
}

#endif // !_CadAnalys_DefectPatch_Wire_Header
