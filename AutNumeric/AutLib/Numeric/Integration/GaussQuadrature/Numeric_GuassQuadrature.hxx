#pragma once
#ifndef _Numeric_GuassQuadrature_Header
#define _Numeric_GuassQuadrature_Header

#include <Numeric_IntegrationBound.hxx>

namespace AutLib
{

	template<class Function, int NbPoints = 8>
	class Numeric_GuassQuadrature
		: public Numeric_IntegrationBound
	{

		typedef Function fun;

		/*Private Data*/

	public:

		typedef NbPoints nbPts;

		Numeric_GuassQuadrature
		(
			const fun& theFunction
		)
			: fun(theFunction)
		{}

		Numeric_GuassQuadrature
		(
			const fun& theFunction,
			const Standard_Real theLower,
			const Standard_Real theUpper
		)
			: fun(theFunction)
			, Numeric_IntegrationBound(theLower, theUpper)
		{}

		void Perform();
	};
}

#include <Numeric_GuassQuadratureI.hxx>

#endif // !_Numeric_GuassQuadrature_Header
