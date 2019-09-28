#pragma once
#ifndef _CrvMaker_FixedParameter_Header
#define _CrvMaker_FixedParameter_Header

#include <CrvMaker_Parameter.hxx>

namespace AutLib
{

	class CrvMaker_FixedParameter
		: public CrvMaker_Parameter
	{

		/*Private Data*/

		Standard_Real theValue_;

	public:

		CrvMaker_FixedParameter()
			: theValue_(0)
		{}

		CrvMaker_FixedParameter(const Standard_Real theValue)
			: theValue_(theValue)
		{}

		void SetValue(const Standard_Real theValue)
		{
			theValue_ = theValue;
		}

		//- override functions

		Standard_Real Value() const override
		{
			return theValue_;
		}
	};
}

#endif // !_CrvMaker_FixedParameter_Header
