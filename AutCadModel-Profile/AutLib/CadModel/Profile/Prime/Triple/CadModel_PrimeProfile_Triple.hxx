#pragma once
#ifndef _CadModel_PrimeProfile_Triple_Header
#define _CadModel_PrimeProfile_Triple_Header

#include <CadModel_PrimeProfile.hxx>

namespace AutLib
{

	template<class PoleType>
	class CadModel_PrimeProfile_Triple
		: public CadModel_PrimeProfile<PoleType>
	{

		/*Private Data*/

		std::shared_ptr<PoleType> theP0_;
		std::shared_ptr<PoleType> theP1_;
		std::shared_ptr<PoleType> theP2_;

	public:

		typedef CadModel_PrimeProfile<PoleType>
			base;

		CadModel_PrimeProfile_Triple()
		{}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<PoleType>, P0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<PoleType>, P1)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<PoleType>, P2)
	};

}

#endif // !_CadModel_PrimeProfile_Triple_Header
