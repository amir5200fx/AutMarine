#pragma once
#ifndef _CadOpetr2d_CutterEdge_Header
#define _CadOpetr2d_CutterEdge_Header

#include <CadOpetr2d_.hxx>

namespace AutLib
{

	class CadOpetr2d_CutterEdge
		: public CadOpetr2d_IntsctEdge
	{

		/*Private Data*/

	public:

		CadOpetr2d_CutterEdge()
		{}

		CadOpetr2d_CutterEdge(const Standard_Integer theIndex)
			: CadOpetr2d_IntsctEdge(theIndex)
		{}

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}

		Standard_Boolean IsCutter() const override
		{
			return Standard_True;
		}


	};
}

#endif // !_CadOpetr2d_CutterEdge_Header
