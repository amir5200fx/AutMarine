#include <Cad2d_Sketch_Engine.hxx>

#include <Entity2d_Box.hxx>
#include <Geom_AdTree.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>

std::shared_ptr<AutLib::Pln_Vertex>
AutLib::Cad2d_Sketch_Engine::PickUpVertex
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(Search());
	const auto& search = *Search();

	auto box = Entity2d_Box::Box(theCoord, Resolution());

	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	search.GeometrySearch(box, vertices);

	if (vertices.empty())
	{
		return nullptr;
	}

	if (vertices.size() IS_EQUAL 1)
	{
		if (SquareDistance(theCoord, vertices[0]->Coord()) <= theResSQ_)
		{
			return vertices[0];
		}
		return nullptr;
	}

	std::shared_ptr<Pln_Vertex> found;
	for (const auto& x : vertices)
	{
		auto dis = SquareDistance(theCoord, x->Coord());
		if (dis <= theResSQ_)
		{
			found = x;
		}
	}

	if (found)
	{
		return std::move(found);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<AutLib::Pln_Vertex> 
AutLib::Cad2d_Sketch_Engine::PickUpVertex
(
	const Pnt2d & theCoord, 
	const Standard_Real thePrec
) const
{
	Debug_Null_Pointer(Search());
	const auto& search = *Search();

	auto box = Entity2d_Box::Box(theCoord, Resolution());

	const auto res = thePrec * thePrec;

	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	search.GeometrySearch(box, vertices);

	if (vertices.empty())
	{
		return nullptr;
	}

	if (vertices.size() IS_EQUAL 1)
	{
		if (SquareDistance(theCoord, vertices[0]->Coord()) <= res)
		{
			return vertices[0];
		}
		return nullptr;
	}

	std::shared_ptr<Pln_Vertex> found;
	for (const auto& x : vertices)
	{
		auto dis = SquareDistance(theCoord, x->Coord());
		if (dis <= res)
		{
			found = x;
		}
	}

	if (found)
	{
		return std::move(found);
	}
	else
	{
		return nullptr;
	}
}

void AutLib::Cad2d_Sketch_Engine::InsertToVertices
(
	const std::shared_ptr<Pln_Vertex>& theVertex
)
{
	theVertices_.insert(std::make_pair(theVertex->Index(), theVertex));
	Search()->InsertToGeometry(theVertex);
}

void AutLib::Cad2d_Sketch_Engine::InsertToEdges
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	theEdges_.insert(std::make_pair(theEdge->Index(), theEdge));
}

void AutLib::Cad2d_Sketch_Engine::RemoveFromVertices
(
	const std::shared_ptr<Pln_Vertex>& theVertex
)
{
	theVertices_.erase(theVertex->Index());
	Search()->RemoveFromGeometry(theVertex);
}

void AutLib::Cad2d_Sketch_Engine::RemoveFromEdges
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	theEdges_.erase(theEdge->Index());
}