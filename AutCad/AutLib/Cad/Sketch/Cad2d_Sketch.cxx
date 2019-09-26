#include <Cad2d_Sketch.hxx>

#include <Adt_AvlTree.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>

std::shared_ptr<AutLib::Pln_Vertex>
AutLib::Cad2d_Sketch::CheckToInsert
(
	const Pnt2d & theCoord,
	const Standard_Real theTol
) const
{
	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	theSearch_.GeometrySearch(Entity2d_Box::Box(theCoord, theTol), vertices);

	if (vertices.empty())
	{
		return nullptr;
	}

	Standard_Real minDis = RealLast();
	std::shared_ptr<Pln_Vertex> vertex = nullptr;
	for (const auto& x : vertices)
	{
		auto dis = Distance(x->Coord(), theCoord);
		if (dis <= theTol)
		{
			if (dis < minDis)
			{
				minDis = dis;
				vertex = x;
			}
		}
	}

	return std::move(vertex);
}

std::shared_ptr<AutLib::Pln_Edge>
AutLib::Cad2d_Sketch::CheckEdge
(
	const std::shared_ptr<Pln_Vertex>& thePt0,
	const std::shared_ptr<Pln_Vertex>& thePt1
)
{
	if (NOT thePt0->NbEdges())
	{
		return nullptr;
	}

	if (NOT thePt1->NbEdges())
	{
		return nullptr;
	}

	std::shared_ptr<Pln_Vertex> other;
	std::vector<std::weak_ptr<Pln_Edge>> edges;
	if (thePt0->NbEdges() < thePt1->NbEdges())
	{
		thePt0->RetrieveEdgesTo(edges);
		other = thePt1;
	}
	else
	{
		thePt1->RetrieveEdgesTo(edges);
		other = thePt0;
	}

	for (const auto& x : edges)
	{
		const auto edge = x.lock();
		Debug_Null_Pointer(edge);

		if (edge->Vtx0() IS_EQUAL other OR edge->Vtx1() IS_EQUAL other)
		{
			return std::move(edge);
		}
	}
	return nullptr;
}

std::shared_ptr<AutLib::Pln_Vertex>
AutLib::Cad2d_Sketch::PickUpVertex
(
	const Pnt2d & theCoord
)
{
	PickUpVertex(theCoord, Tolerance());
}

std::shared_ptr<AutLib::Pln_Vertex>
AutLib::Cad2d_Sketch::PickUpVertex
(
	const Pnt2d & theCoord,
	const Standard_Real thePrec
)
{
	auto vertex = CheckToInsert(theCoord, thePrec);

	if (vertex)
	{
		PickedUpVertex = Standard_True;
		return std::move(vertex);
	}

	theNbVertices_++;

	vertex =
		std::make_shared<Pln_Vertex>
		(
			theNbVertices_,
			"New Vertex " + std::to_string(theNbVertices_),
			theCoord);

	theSearch_.InsertToGeometry(vertex);
	theVertices_.insert(std::make_pair(theNbVertices_, vertex));

	PickedUpVertex = Standard_False;
	return std::move(vertex);
}

std::shared_ptr<AutLib::Pln_Edge>
AutLib::Cad2d_Sketch::PickUpEdge
(
	const std::shared_ptr<Pln_Vertex>& thePt0,
	const std::shared_ptr<Pln_Vertex>& thePt1
)
{
	if (NOT thePt0)
	{
		FatalErrorIn("std::shared_ptr<Pln_Edge> PickUpEdge(const std::shared_ptr<Pln_Vertex>& thePt0, const std::shared_ptr<Pln_Vertex>& thePt1)")
			<< "Empty vertex" << endl
			<< abort(FatalError);
	}

	if (NOT thePt1)
	{
		FatalErrorIn("std::shared_ptr<Pln_Edge> PickUpEdge(const std::shared_ptr<Pln_Vertex>& thePt0, const std::shared_ptr<Pln_Vertex>& thePt1)")
			<< "Empty vertex" << endl
			<< abort(FatalError);
	}

	PickedUpEdge = Standard_False;

	auto check = CheckEdge(thePt0, thePt1);
	if (check)
	{
		PickedUpEdge = Standard_True;
		return std::move(check);
	}

	Debug_Null_Pointer(Info());
	Debug_Null_Pointer(Info()->CurveInfo());

	const auto& curveInfo = Info()->CurveInfo();

	auto curve =
		Pln_Curve::MakeLineSegment(thePt0->Coord(), thePt1->Coord(), curveInfo);

	auto edge =
		std::make_shared<Pln_Edge>(thePt0, thePt1, curve, Info()->DiscreteEdge());

	theNbEdges_++;

	thePt0->InsertToEdges(edge);
	thePt1->InsertToEdges(edge);

	theEdges_.insert(std::make_pair(theNbEdges_, edge));

	return std::move(edge);
}

std::vector<std::shared_ptr<AutLib::Pln_Edge>>
AutLib::Cad2d_Sketch::CreateRectangle
(
	const std::shared_ptr<Pln_Vertex>& thePt0,
	const std::shared_ptr<Pln_Vertex>& thePt1
)
{
	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(4);

	auto P10 = PickUpVertex(Pnt2d(thePt1->Coord().X(), thePt0->Coord().Y()));
	auto P01 = PickUpVertex(Pnt2d(thePt0->Coord().X(), thePt1->Coord().Y()));

	edges.push_back(PickUpEdge(thePt0, P10));
	edges.push_back(PickUpEdge(P10, thePt1));
	edges.push_back(PickUpEdge(thePt1, P01));
	edges.push_back(PickUpEdge(P01, thePt0));

	return std::move(edges);
}

namespace AutLib
{

	Standard_Boolean CheckFreeEdge(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges)
	{
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);

			const auto& v0 = x->Vtx0();
			const auto& v1 = x->Vtx1();

			if (v0->IsFree()) return Standard_True;
			if (v1->IsFree()) return Standard_True;
		}

		return Standard_False;
	}

	Standard_Integer Next
	(
		const std::vector<std::weak_ptr<Pln_Edge>>& edges,
		const Adt_AvlTree<std::shared_ptr<Pln_Edge>>& Register,
		std::shared_ptr<Pln_Edge>& theEdge
	)
	{
		Standard_Integer k = 0;
		for (const auto& x : edges)
		{
			auto edge = x.lock();
			Debug_Null_Pointer(edge);

			if (Register.IsContains(edge))
			{
				k++;
				theEdge = edge;
			}
		}
		return k;
	}

	std::vector<std::shared_ptr<Pln_Edge>>
		TrackWire
		(
			const std::shared_ptr<Pln_Edge>& theEdge,
			Adt_AvlTree<std::shared_ptr<Pln_Edge>>& Register
		)
	{
		auto v1 = theEdge->Vtx1();
		std::vector<std::weak_ptr<Pln_Edge>> edges;
		v1->RetrieveEdgesTo(edges);

		std::vector<std::shared_ptr<Pln_Edge>> Tracked;
		Tracked.push_back(theEdge);

		std::shared_ptr<Pln_Edge> next;
		do
		{
			next = nullptr;
			auto size = Next(edges, Register, next);

			if (NOT size)
			{
				break;
			}

			if (size NOT_EQUAL 1)
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Wire" << endl
					<< abort(FatalError);
			}

			Tracked.push_back(next);
			Register.Remove(next);

			if (next->Vtx0() IS_EQUAL v1)
			{
				v1 = next->Vtx1();
				v1->RetrieveEdgesTo(edges);
			}
			else if (next->Vtx1() IS_EQUAL v1)
			{
				v1 = next->Vtx0();
				v1->RetrieveEdgesTo(edges);

				next->Reverse();
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Wire" << endl
					<< abort(FatalError);
			}
		} while (next);

		return std::move(Tracked);
	}

	std::vector<std::shared_ptr<Pln_Edge>>
		SortWire
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
		)
	{
		Adt_AvlTree<std::shared_ptr<Pln_Edge>> Register;
		Register.SetComparableFunction(&Pln_Edge::IsLess);

		forThose(Index, 1, theEdges.size() - 1)
		{
			Register.Insert(theEdges[Index]);
		}

		auto sorted = TrackWire(theEdges[0], Register);
		return std::move(sorted);
	}
}

std::shared_ptr<AutLib::Pln_Wire>
AutLib::Cad2d_Sketch::MakeWire
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
) const
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		if (x->Wire().lock())
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Wire>> MakeWire(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges) const")
				<< "the edge is already belong to a wire" << endl
				<< abort(FatalError);
		}
	}

	if (theEdges.size() IS_EQUAL 1)
	{
		if (NOT theEdges[0]->IsRing())
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Wire>> MakeWire(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges) const")
				<< "Invalid Wire" << endl
				<< abort(FatalError);
		}

		auto wire = std::make_shared<Pln_Wire>(0, theEdges);
		theEdges[0]->SetWire(wire);

		return std::move(wire);
	}

	if (theEdges.size() < 3)
	{
		FatalErrorIn("std::vector<std::shared_ptr<Pln_Wire>> MakeWire(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges) const")
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}

	if (CheckFreeEdge(theEdges))
	{
		FatalErrorIn("std::vector<std::shared_ptr<Pln_Wire>> MakeWire(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges) const")
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}

	auto sorted = SortWire(theEdges);

	auto wire = std::make_shared<Pln_Wire>(0, sorted);

	for (const auto& x : sorted)
	{
		Debug_Null_Pointer(x);
		x->SetWire(wire);
	}

	return std::move(wire);
}