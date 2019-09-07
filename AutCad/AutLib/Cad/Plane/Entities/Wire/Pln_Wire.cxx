#include <Pln_Wire.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Chain.hxx>
#include <GeoProcessor.hxx>
#include <Adt_AvlTree.hxx>

void AutLib::Pln_Wire::CalcBoundingBox()
{
	Debug_Null_Pointer(Edges());
	const auto& edges = *Edges();

	if (edges.empty())
	{
		FatalErrorIn("void AutLib::Plane_Wire::CalcBoundingBox()")
			<< "Empty List"
			<< abort(FatalError);
	}

	const auto iter = edges.cbegin();
	Debug_Null_Pointer(*iter);
	Debug_Null_Pointer((*iter)->Curve());

	auto box = (*iter)->Curve()->BoundingBox();
	while (iter NOT_EQUAL edges.cend())
	{
		const auto& x = (*iter)->Curve();

		Debug_Null_Pointer(x);
		box = Entity2d_Box::Union(box, x->BoundingBox());
	}
	theBoundingBox_ = std::make_shared<Entity2d_Box>(box);
}

void AutLib::Pln_Wire::CheckWire(const edgeList & theEdges) const
{
	Debug_Null_Pointer(Edges());
	const auto& edges = *Edges();

	if (edges.size() IS_EQUAL 1)
	{
		if (NOT edges[0]->IsRing())
		{
			FatalErrorIn("void CheckWire(const edgeList& theEdges)")
				<< "Invalid Wire: the edge is not a ring" << endl
				<< abort(FatalError);
		}
		return;
	}

	forThose(Index, 1, edges.size() - 1)
	{
		const auto& edge0 = edges[Index - 1];
		const auto& edge1 = edges[Index];

		if (edge0->Vtx1() NOT_EQUAL edge1->Vtx0())
		{
			FatalErrorIn("void CheckWire(const edgeList& theEdges)")
				<< "Invalid Wire" << endl
				<< abort(FatalError);
		}
	}

	const auto& last = edges[edges.size() - 1];
	const auto& first = edges[0];

	if (last->Vtx1() NOT_EQUAL first->Vtx0())
	{
		FatalErrorIn("void CheckWire(const edgeList& theEdges)")
			<< "Invalid Wire: the wire is not closed" << endl
			<< abort(FatalError);
	}
}

void AutLib::Pln_Wire::CreateWire
(
	const std::shared_ptr<edgeList>& theEdges
)
{
	if (NOT theEdges)
	{
		FatalErrorIn("void CreateWire(const std::shared_ptr<edgeList>& theEdges)")
			<< "Null edge list!" << endl
			<< abort(FatalError);
	}

	CheckWire(*theEdges);

	theEdges_ = theEdges;

	theOrientation_ = RetrieveOrientation(*this);
}

void AutLib::Pln_Wire::Reverse()
{
	if (Orientation() IS_EQUAL Pln_Orientation_Unknown)
	{
		FatalErrorIn("void AutLib::Plane_Wire::Reverse()")
			<< "Unknown orientation"
			<< abort(FatalError);
	}

	for (auto& x : *theEdges_)
	{
		Debug_Null_Pointer(x);
		x->Reverse();
	}

	std::reverse(theEdges_->begin(), theEdges_->end());
	theOrientation_ = AutLib::Reverse(Orientation());
}

void AutLib::Pln_Wire::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
) const
{
	theVertices.reserve(NbEdges());
	for (const auto& x : *Edges())
	{
		theVertices.push_back(x->Vtx0());
	}
}

namespace AutLib
{

	std::shared_ptr<AutLib::Pln_Edge>
		Next
		(
			const std::shared_ptr<AutLib::Pln_Edge>& theEdge
		)
	{
		if (theEdge->IsRing())
		{
			FatalErrorIn("std::shared_ptr<Pln_Edge> Next(const std::shared_ptr<Pln_Edge>& theEdge)")
				<< "Invalid wire: contains at least one ring!" << endl
				<< abort(FatalError);
		}

		const auto& vtx = theEdge->Vtx1();
		if (NOT vtx)
		{
			FatalErrorIn("std::shared_ptr<Plane_Edge> Next(const std::shared_ptr<Plane_Edge>& theEdge)")
				<< "Null vertex" << endl
				<< abort(FatalError);
		}

		if (NOT vtx->IsManifold())
		{
			FatalErrorIn("std::shared_ptr<Plane_Edge> Next(const std::shared_ptr<Plane_Edge>& theEdge)")
				<< "The vertex is non-manifold" << endl
				<< abort(FatalError);
		}

		std::vector<std::weak_ptr<Pln_Edge>> list;
		vtx->RetrieveEdgesTo(list);

		Debug_If_Condition(list.size() NOT_EQUAL 2);

		Debug_Null_Pointer(list[0].lock());
		Debug_Null_Pointer(list[1].lock());

		auto edge0 = list[0].lock();
		auto edge1 = list[1].lock();

		if (edge0 IS_EQUAL theEdge) return edge1;
		else return edge0;
	}

	std::shared_ptr<AutLib::Pln_Wire>
		TrackWire
		(
			Adt_AvlTree<std::shared_ptr<Pln_Edge>>& theRegister
		)
	{
		if (theRegister.IsEmpty())
		{
			FatalErrorIn("wire_ptr TrackWire(Adt_AvlTree<std::shared_ptr<Pln_Edge>>& theRegister)")
				<< "Empty List" << endl
				<< abort(FatalError);
		}

		auto list = std::make_shared<std::vector<std::shared_ptr<Pln_Edge>>>();

		std::shared_ptr<Pln_Edge> edge;
		theRegister.Root(edge);

		if (edge->IsRing())
		{
			list->push_back(edge);
			theRegister.Remove(edge);
			auto wire = std::make_shared<Pln_Wire>(0, list);
			return std::move(wire);
		}

		auto root = edge;
		list->push_back(edge);

		Standard_Boolean cycle = Standard_False;
		while (NOT theRegister.IsEmpty())
		{
			theRegister.Remove(edge);
			edge = Next(edge);

			if (edge IS_EQUAL root)
			{
				cycle = Standard_True;
				break;
			}
			list->push_back(edge);
		}

		if (NOT cycle)
		{
			FatalErrorIn("wire_ptr TrackWire(Adt_AvlTree<std::shared_ptr<Plane_Edge>>& theRegister)")
				<< "found no wire" << endl
				<< abort(FatalError);
		}

		auto wire = std::make_shared<Pln_Wire>(0, list);
		return std::move(wire);
	}
}

std::vector<std::shared_ptr<AutLib::Pln_Wire>>
AutLib::Pln_Wire::RetrieveWires
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	if (theEdges.empty())
	{
		FatalErrorIn("wireList RetrieveWires()")
			<< "Empty List" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Pln_Wire>> list;

	Adt_AvlTree<std::shared_ptr<Pln_Edge>> Register;
	Register.SetComparableFunction(&Pln_Edge::IsLess);

	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		Register.Insert(x);
	}

	while (true)
	{
		list.push_back(TrackWire(Register));
		if (Register.IsEmpty())
		{
			break;
		}
	}

	Standard_Integer K = 0;
	for (auto& x : list)
	{
		x->SetIndex(++K);
	}
	return std::move(list);
}

AutLib::Pln_Orientation
AutLib::Pln_Wire::RetrieveOrientation
(
	const Pln_Wire & theWire
)
{
	std::vector<Pnt2d> Pts;

	const auto& edges = *theWire.Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		if (!x->Approx())
		{
			FatalErrorIn("Plane_Orientation RetrieveOrientation(const Plane_Wire& theWire)")
				<< " the edge has not an approximation curve!" << endl
				<< abort(FatalError);
		}

		const auto& chain = x->Approx();
		const auto& appx_pts = chain->Points();

		for (const auto& pt : appx_pts)
		{
			Pts.push_back(pt);
		}
	}

	if (Processor::IsCcwOrder(Pts)) return Pln_Orientation_CCW;
	else return Pln_Orientation_CW;
}