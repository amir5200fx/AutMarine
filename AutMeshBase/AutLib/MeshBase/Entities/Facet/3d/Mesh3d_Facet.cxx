#include <Mesh3d_Facet.hxx>

#include <GeoProcessor.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	template<>
	Standard_Boolean Mesh3d_Facet::IsLeftSide(const Pnt3d& theCoord) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());
		Debug_Null_Pointer(Node2());

		const auto& n0 = *Node0();
		const auto& n1 = *Node1();
		const auto& n2 = *Node2();

		return Processor::IsPointLeftFacet_cgal(theCoord, n0.Coord(), n1.Coord(), n2.Coord());
	}

	template<>
	Standard_Boolean Mesh3d_Facet::IsRightSide(const Pnt3d& theCoord) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());
		Debug_Null_Pointer(Node2());

		const auto& n0 = *Node0();
		const auto& n1 = *Node1();
		const auto& n2 = *Node2();

		return Processor::IsPointRightFacet_cgal(theCoord, n0.Coord(), n1.Coord(), n2.Coord());
	}
}