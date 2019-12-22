#pragma once
#ifndef _CadModel_ProfilePole_Backward_Header
#define _CadModel_ProfilePole_Backward_Header

#include <CadModel_ProfilePole_Dangle.hxx>

namespace AutLib
{

	template<class PoleTraits>
	class CadModel_ProfilePole_Backward
		: public CadModel_ProfilePole_Dangle<PoleTraits>
	{

		/*Private Data*/

	public:

		typedef CadModel_ProfilePole_Dangle<PoleTraits>
			base;

		CadModel_ProfilePole_Backward()
		{}

		Standard_Boolean IsBackward() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_CadModel_ProfilePole_Backward_Header
