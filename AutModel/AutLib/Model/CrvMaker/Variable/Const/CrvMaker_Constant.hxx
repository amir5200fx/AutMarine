#pragma once
#ifndef _CrvMaker_Constant_Header
#define _CrvMaker_Constant_Header

#include <CrvMaker_Variable.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	class CrvMaker_Constant
		: public CrvMaker_Variable
	{

		/*Private Data*/

		Standard_Real theValue_;

	public:

		CrvMaker_Constant(const Standard_Real theValue)
			: theValue_(theValue)
		{}

		Standard_Real Value() const override
		{
			return theValue_;
		}
	};
}

#endif // !_CrvMaker_Constant_Header
