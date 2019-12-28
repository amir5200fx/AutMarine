#pragma once
#ifndef _CadOpert2d_IntsctPlnEdge_Header
#define _CadOpert2d_IntsctPlnEdge_Header

#include <CadOpert2d_IntsctCmpEdge.hxx>

namespace AutLib
{

	class CadOpert2d_IntsctPlnEdge
		: public CadOpert2d_IntsctCmpEdge
	{

		/*private Data*/

	protected:

		CadOpert2d_IntsctPlnEdge()
		{}

		CadOpert2d_IntsctPlnEdge(const Standard_Integer theIndex)
			: CadOpert2d_IntsctCmpEdge(theIndex)
		{}

	public:

		Standard_Boolean IsSubEdge() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsOrthogonal() const
		{
			return Standard_False;
		}
	};
}

#endif // !_CadOpert2d_IntsctPlnEdge_Header
