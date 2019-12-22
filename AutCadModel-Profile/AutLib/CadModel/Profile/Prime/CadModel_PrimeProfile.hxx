#pragma once
#ifndef _CadModel_PrimeProfile_Header
#define _CadModel_PrimeProfile_Header

#include <CadModel_Profile.hxx>

namespace AutLib
{

	template<class PoleType>
	class CadModel_PrimeProfile
		: public CadModel_Profile<PoleType>
	{

		/*Private Data*/

	protected:

	public:

		Standard_Boolean IsPrime() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_CadModel_PrimeProfile_Header
