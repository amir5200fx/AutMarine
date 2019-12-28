#pragma once
#ifndef _CadOpert2d_IntsctCutter_Dangle_Header
#define _CadOpert2d_IntsctCutter_Dangle_Header

#include <CadOpert2d_IntsctCutter.hxx>

namespace AutLib
{

	class CadOpert2d_IntsctCutter_Dangle
		: public CadOpert2d_IntsctCutter
	{

		/*Private Data*/

	public:

		CadOpert2d_IntsctCutter_Dangle()
		{}

		CadOpert2d_IntsctCutter_Dangle(const Standard_Integer theIndex)
			: CadOpert2d_IntsctCutter(theIndex)
		{}

		Standard_Boolean IsDangle() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_CadOpert2d_IntsctCutter_Dangle_Header
