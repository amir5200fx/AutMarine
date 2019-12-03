#pragma once
#ifndef _CadAnalys_DefectPatch_OpenWire_Header
#define _CadAnalys_DefectPatch_OpenWire_Header

#include <CadAnalys_DefectPatch_Wire.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_DefectPatch_OpenWire
		: public CadAnalys_DefectPatch_Wire<SurfType>
	{

		/*Private Data*/

	public:

		typedef CadAnalys_DefectPatch_Wire<SurfType>
			base;

		CadAnalys_DefectPatch_OpenWire(const SurfType& theSurface)
			: CadAnalys_DefectPatch_Wire<SurfType>(theSurface)
		{}


	};
}

#endif // !_CadAnalys_DefectPatch_OpenWire_Header
