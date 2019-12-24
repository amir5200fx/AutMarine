#pragma once
#ifndef _CadOpetr2d_EdgeEdgeIntsct_Info_Header
#define _CadOpetr2d_EdgeEdgeIntsct_Info_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>

namespace AutLib
{

	class CadOpetr2d_EdgeEdgeIntsct_Info
	{

		/*Private Data*/

		Standard_Real theTolerance_;

	public:

		static const Standard_Real DEFAULT_TOLERANCE;

		CadOpetr2d_EdgeEdgeIntsct_Info()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
	};
}

#endif // !_CadOpetr2d_EdgeEdgeIntsct_Info_Header
