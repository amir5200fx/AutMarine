#include <Pln_Vertex.hxx>

#include <Pln_Ring.hxx>

namespace AutLib
{

	const std::shared_ptr<Pln_Vertex> Pln_Vertex::null = std::make_shared<Pln_Vertex>();
}

Standard_Boolean AutLib::Pln_Vertex::IsFree() const
{
	return NbEdges() IS_EQUAL 1;
}

Standard_Boolean AutLib::Pln_Vertex::IsOrphan() const
{
	return NbEdges() IS_EQUAL 0;
}

Standard_Boolean AutLib::Pln_Vertex::IsRingPoint() const
{
	if (NbEdges() NOT_EQUAL 1) return Standard_False;

	std::vector<std::weak_ptr<Pln_Edge>> edges;
	RetrieveEdgesTo(edges);

	if (std::dynamic_pointer_cast<Pln_Ring>(edges[0].lock()))
	{
		return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean AutLib::Pln_Vertex::IsManifold() const
{
	if (IsRingPoint()) return Standard_True;
	else if (NbEdges() IS_EQUAL 2) return Standard_True;
	return Standard_False;
}

void AutLib::Pln_Vertex::InsertToEdges(const std::shared_ptr<Pln_Edge>& theEdge)
{
	theEdges_.insert(std::make_pair(theEdge->Index(), theEdge));
}

void AutLib::Pln_Vertex::RemoveFromEdges(const std::shared_ptr<Pln_Edge>& theEdge)
{
	theEdges_.erase(theEdge->Index());
}

void AutLib::Pln_Vertex::RetrieveEdgesTo(std::vector<std::weak_ptr<Pln_Edge>>& theEdges) const
{
	theEdges.reserve(theEdges_.size());
	for (const auto& x : theEdges_)
	{
		theEdges.push_back(x.second);
	}
}