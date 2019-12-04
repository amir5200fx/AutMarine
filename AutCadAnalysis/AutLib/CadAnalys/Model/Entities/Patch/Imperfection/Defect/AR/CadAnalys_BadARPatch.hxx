#pragma once
#ifndef _CadAnalys_BadARPatch_Header
#define _CadAnalys_BadARPatch_Header

#include <CadAnalys_DefectPatch.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_BadARPatch
		: public CadAnalys_DefectPatch<SurfType>
	{

		/*Private Data*/

	public:

		typedef CadAnalys_DefectPatch<SurfType>
			base;

		CadAnalys_BadARPatch(const std::shared_ptr<SurfType>& theSurface)
			: CadAnalys_DefectPatch<SurfType>(theSurface)
		{}

		static std::pair<Standard_Integer, Standard_Real> CalcMaxAR(const SurfType& theSurface);
	};
}

#include <CadAnalys_BadARPatchI.hxx>

#endif // !_CadAnalys_BadARPatch_Header
