#pragma once
#ifndef _CadModel_ProfilePole_Forward_Header
#define _CadModel_ProfilePole_Forward_Header

#include <CadModel_ProfilePole_Dangle.hxx>

namespace AutLib
{

	template<class PoleTraits>
	class CadModel_ProfilePole_Forward
		: public CadModel_ProfilePole_Dangle<PoleTraits>
	{

		/*Private Data*/

	public:

		typedef CadModel_ProfilePole_Dangle<PoleTraits>
			base;

		CadModel_ProfilePole_Forward()
		{}

		Standard_Boolean IsForward() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_CadModel_ProfilePole_Forward_Header
