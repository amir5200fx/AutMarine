#pragma once
#ifndef _CadOpetr_IntsctVertx_Header
#define _CadOpetr_IntsctVertx_Header

#include <Pln_Vertex.hxx>

namespace AutLib
{

	class CadOpetr_IntsctVertx
		: public Pln_Vertex
	{

		/*Private Data*/

	public:

		CadOpetr_IntsctVertx()
		{}

		CadOpetr_IntsctVertx
		(
			const Standard_Integer theIndex
		)
			: Pln_Vertex(theIndex)
		{}

		CadOpetr_IntsctVertx
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Pln_Vertex(theIndex, theName)
		{}

		CadOpetr_IntsctVertx
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: Pln_Vertex(theIndex, theName, theCoord)
		{}
	};
}

#endif // !_CadOpetr_IntsctVertx_Header
