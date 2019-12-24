#pragma once
#ifndef _CadOpetr2d_IntsctVertx_Header
#define _CadOpetr2d_IntsctVertx_Header

#include <Pln_Vertex.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpetr2d_IntsctEdge;

	class CadOpetr2d_IntsctVertx
		: public Pln_Vertex
	{

		/*Private Data*/

		std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpetr2d_IntsctEdge>
			>
			theIntsctEdges_;

	public:

		CadOpetr2d_IntsctVertx()
		{}

		CadOpetr2d_IntsctVertx
		(
			const Standard_Integer theIndex
		)
			: Pln_Vertex(theIndex)
		{}

		CadOpetr2d_IntsctVertx
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: Pln_Vertex(theIndex, theName, theCoord)
		{}

		std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpetr2d_IntsctEdge>
			>& IntsctEdges()
		{
			return theIntsctEdges_;
		}

		void InsertToIntsctEdges
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<CadOpetr2d_IntsctEdge>& theEdge
		)
		{
			theIntsctEdges_.insert(std::make_pair(theIndex, theEdge));
		}
	};
}

#endif // !_CadOpetr2d_IntsctVertx_Header
