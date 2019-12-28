#pragma once
#ifndef _CadOpert2d_IntsctVertx_Header
#define _CadOpetr2d_IntsctVertx_Header

#include <Global_Indexed.hxx>
#include <Global_AccessMethod.hxx>
#include <Pln_Vertex.hxx>

#include <memory>
#include <map>

namespace AutLib
{

	// Forward Declarations
	class CadOpert2d_IntsctCmpEdge;
	class CadOpert2d_IntsctPoint;

	class CadOpert2d_IntsctVertx
		: public Pln_Vertex
	{

		/*Private Data*/

		std::shared_ptr<CadOpert2d_IntsctPoint> theEntity_;

		std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpert2d_IntsctCmpEdge>
			>
			theIntsctEdges_;

	public:

		CadOpert2d_IntsctVertx()
		{}

		CadOpert2d_IntsctVertx
		(
			const Standard_Integer theIndex, 
			const Pnt2d& theCoord,
			const std::shared_ptr<CadOpert2d_IntsctPoint>& theEntity
		)
			: Pln_Vertex(theIndex, theCoord)
			, theEntity_(theEntity)
		{}

		std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpert2d_IntsctCmpEdge>
			>& IntsctEdges()
		{
			return theIntsctEdges_;
		}

		const std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpert2d_IntsctCmpEdge>
			>& IntsctEdges() const
		{
			return theIntsctEdges_;
		}

		void InsertToIntsctEdges
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<CadOpert2d_IntsctCmpEdge>& theEdge
		)
		{
			theIntsctEdges_.insert(std::make_pair(theIndex, theEdge));
		}

		Standard_Boolean IsIntersection() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctPoint>, Entity)
	};
}

#endif // !_CadOpert2d_IntsctVertx_Header
