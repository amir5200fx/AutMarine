#pragma once
#ifndef _GModel_FixWireInfo_Header
#define _GModel_FixWireInfo_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>

namespace AutLib
{

	class GModel_FixWireInfo
	{

		/*Private Data*/

		Standard_Real thePrecision_;
		Standard_Real theMaxTolerance_;
		Standard_Real theMinTolerance_;

	public:

		static const Standard_Real DEFAULT_PRECISION;
		static const Standard_Real DEFAULT_MAX_TOLERANCE;
		static const Standard_Real DEFAULT_MIN_TOLERANCE;

		GModel_FixWireInfo()
			: thePrecision_(DEFAULT_PRECISION)
			, theMinTolerance_(DEFAULT_MIN_TOLERANCE)
			, theMaxTolerance_(DEFAULT_MAX_TOLERANCE)
		{}

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Precision)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MaxTolerance)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MinTolerance)
	};
}

#endif // !_GModel_FixWireInfo_Header
