#pragma once
#ifndef _CrvMaker_Variable_Header
#define _CrvMaker_Variable_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	class CrvMaker_Variable
	{

		/*Private Data*/

	protected:

		CrvMaker_Variable()
		{}

	public:

		virtual Standard_Real Value() const = 0;
	};
}

#endif // !_CrvMaker_Variable_Header
