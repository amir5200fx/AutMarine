#pragma once
#ifndef _CadOpts_PlnIntsct_Info_Header
#define _CadOpts_PlnIntsct_Info_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>

namespace AutLib
{

	class CadOpts_PlnIntsct_Info
	{

		/*Private Data*/

		Standard_Real theTolerance_;

	public:

		static const Standard_Real DEFAULT_TOLERANCE;

		CadOpts_PlnIntsct_Info()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
	};
}

#endif // !_CadOpts_PlnIntsct_Info_Header
