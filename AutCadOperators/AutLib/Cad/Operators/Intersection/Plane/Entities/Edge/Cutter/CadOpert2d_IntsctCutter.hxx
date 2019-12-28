#pragma once
#ifndef _CadOpert2d_IntsctCutter_Header
#define _CadOpert2d_IntsctCutter_Header

#include <CadOpert2d_IntsctCmpEdge.hxx>

namespace AutLib
{

	class CadOpert2d_IntsctCutter
		: public CadOpert2d_IntsctCmpEdge
	{

		/*private Data*/

	protected:

		CadOpert2d_IntsctCutter()
		{}

		CadOpert2d_IntsctCutter
		(
			const Standard_Integer theIndex
		)
			: CadOpert2d_IntsctCmpEdge(theIndex)
		{}

	public:

		Standard_Boolean IsCutter() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsDangle() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsClamped() const
		{
			return Standard_False;
		}
	};
}

#endif // !_CadOpert2d_IntsctCutter_header
