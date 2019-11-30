#pragma once
#ifndef _CadOpts_PlnIntsct_Vertex_Header
#define _CadOpts_PlnIntsct_Vertex_Header

#include <Pln_Vertex.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpts_PlnIntsct_Edge;

	class CadOpts_PlnIntsct_Vertex
		: public Pln_Vertex
	{

		/*Private Data*/

		std::map
			<
			Standard_Integer,
			std::weak_ptr<CadOpts_PlnIntsct_Edge>
			> theIntEdges_;

	public:

		CadOpts_PlnIntsct_Vertex()
		{}

		CadOpts_PlnIntsct_Vertex(const Standard_Integer theIndex)
			: Pln_Vertex(theIndex)
		{}

		CadOpts_PlnIntsct_Vertex
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: Pln_Vertex(theIndex, theCoord)
		{}

		CadOpts_PlnIntsct_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: Pln_Vertex(theIndex, theName, theCoord)
		{}

		Standard_Integer NbIntEdges() const
		{
			return (Standard_Integer)theIntEdges_.size();
		}

		const std::map
			<
			Standard_Integer,
			std::weak_ptr<CadOpts_PlnIntsct_Edge>
			>& IntEdges() const
		{
			return theIntEdges_;
		}

		void InsertToIntEdges(const std::shared_ptr<CadOpts_PlnIntsct_Edge>& theEdge);


	};
}

#endif // !_CadOpts_PlnIntsct_Vertex_Header
