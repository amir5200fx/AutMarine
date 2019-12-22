#pragma once
#ifndef _CadModel_PrimeProfile_Quadruple_Header
#define _CadModel_PrimeProfile_Quadruple_Header

#include <CadModel_PrimeProfile.hxx>

namespace AutLib
{

	template<class PoleType>
	class CadModel_PrimeProfile_Quadruple
		: public CadModel_PrimeProfile<PoleType>
	{

		/*private Data*/

		std::shared_ptr<PoleType> theP0_;
		std::shared_ptr<PoleType> theP1_;
		std::shared_ptr<PoleType> theP2_;
		std::shared_ptr<PoleType> theP3_;

	public:

		typedef CadModel_PrimeProfile<PoleType>
			base;

		CadModel_PrimeProfile_Quadruple()
		{}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<PoleType>, P0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<PoleType>, P1)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<PoleType>, P2)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<PoleType>, P3)
	};
}

#endif // !_CadModel_PrimeProfile_Quadruple_Header
