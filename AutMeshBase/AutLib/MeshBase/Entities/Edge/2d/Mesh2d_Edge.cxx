#include <Mesh2d_Edge.hxx>

#include <GeoProcessor.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	template<>
	template<>
	Standard_Boolean Mesh2d_Edge::IsLeftSide<Standard_Boolean>
		(
			const Pnt2d& theCoord
			) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());

		const auto& n0 = *Node0();
		const auto& n1 = *Node1();

		return Processor::IsPointRightEdge_cgal(theCoord, n0.Coord(), n1.Coord());
	}

	template<>
	template<>
	Standard_Boolean Mesh2d_Edge::IsRightSide<Standard_Boolean>
		(
			const Pnt2d& theCoord
			) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());

		const auto& n0 = *Node0();
		const auto& n1 = *Node1();

		return Processor::IsPointLeftEdge_cgal(theCoord, n0.Coord(), n1.Coord());
	}
}