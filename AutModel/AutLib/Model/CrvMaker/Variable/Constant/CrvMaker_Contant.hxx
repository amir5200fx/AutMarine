#pragma once
#ifndef _CrvMaker_Contant_Header
#define _CrvMaker_Contant_Header

#include <CrvMaker_Variable.hxx>

namespace AutLib
{

	class CrvMaker_Contant
		: public CrvMaker_Variable
	{

		/*Private Data*/

		Standard_Real theValue_;

	public:

		CrvMaker_Contant()
			: theValue_(0)
		{}

		CrvMaker_Contant(const Standard_Real theValue)
			: theValue_(theValue)
		{}

		void SetValue(const Standard_Real theValue)
		{
			theValue_ = theValue;
		}

		Standard_Real Value() const override
		{
			return theValue_;
		}
	};
}

#endif // !_CrvMaker_Contant_Header
