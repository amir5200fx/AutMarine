#pragma once
#ifndef _CadAnalys_DefectPatch_OrderWire_Header
#define _CadAnalys_DefectPatch_OrderWire_Header

#include <CadAnalys_DefectPatch_Wire.hxx>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_DefectPatch_OrderWire
		: public CadAnalys_DefectPatch_Wire<SurfType>
	{

		/*Private Data*/

	public:

		typedef CadAnalys_DefectPatch_Wire<SurfType>
			base;

		CadAnalys_DefectPatch_OrderWire(const SurfType& theSurface)
			: CadAnalys_DefectPatch_Wire<SurfType>(theSurface)
		{}
	};
}

#endif // !_CadAnalys_DefectPatch_OrderWire_Header
