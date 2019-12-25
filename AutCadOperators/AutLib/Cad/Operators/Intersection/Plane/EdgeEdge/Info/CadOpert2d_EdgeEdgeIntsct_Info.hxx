#pragma once
#ifndef _CadOpert2d_EdgeEdgeIntsct_Info_Header
#define _CadOpert2d_EdgeEdgeIntsct_Info_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>

namespace AutLib
{

	class CadOpert2d_EdgeEdgeIntsct_Info
	{

		/*Private Data*/

		Standard_Real theTolerance_;

	public:

		static const Standard_Real DEFAULT_TOLERANCE;

		CadOpert2d_EdgeEdgeIntsct_Info()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
	};
}

#endif // !_CadOpert2d_EdgeEdgeIntsct_Info_Header
