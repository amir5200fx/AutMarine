#pragma once
#ifndef _CadOpetr2d_SubEdge_Header
#define _CadOpetr2d_SubEdge_Header

#include <CadOpetr_IntsctEdge.hxx>

namespace AutLib
{

	class CadOpetr2d_SubEdge
		: public CadOpetr2d_IntsctEdge
	{

		/*Private Data*/

	public:

		CadOpetr2d_SubEdge()
		{}

		CadOpetr2d_SubEdge(const Standard_Integer theIndex)
			: CadOpetr2d_IntsctEdge(theIndex)
		{}

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}

		Standard_Boolean IsSubdivided() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_CadOpetr2d_SubEdge_Header
