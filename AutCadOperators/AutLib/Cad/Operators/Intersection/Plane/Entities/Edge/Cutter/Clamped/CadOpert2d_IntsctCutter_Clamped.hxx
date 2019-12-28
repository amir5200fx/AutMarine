#pragma once
#ifndef _CadOpert2d_IntsctCutter_Clamped_Header
#define _CadOpert2d_IntsctCutter_Clamped_Header

#include <CadOpert2d_IntsctCutter.hxx>

namespace AutLib
{

	class CadOpert2d_IntsctCutter_Clamped
		: public CadOpert2d_IntsctCutter
	{

		/*Private Data*/

	protected:

		CadOpert2d_IntsctCutter_Clamped()
		{}

		CadOpert2d_IntsctCutter_Clamped(const Standard_Integer theIndex)
			: CadOpert2d_IntsctCutter(theIndex)
		{}

	public:

		Standard_Boolean IsClamped() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsOrthogonal() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}
	};
}

#endif // !_CadOpert2d_IntsctCutter_Clamped_Header
