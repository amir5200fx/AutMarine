#include <Cad2d_Plane.hxx>

#include <Cad_CurveInfo.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Vertex.hxx>
#include <Cad_Tools.hxx>
#include <Cad2d_Plane_System.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

void AutLib::Cad2d_Plane::SplitByWires()
{
	if (theEdges_->NbBlocks() > 1)
	{
		theEdges_->CompactBlocks("Default Block Edge");
	}

	if (theEdges_->NbBlocks() NOT_EQUAL 1)
	{
		FatalErrorIn("void AutLib::Cad2d_Plane::SplitByWires()")
			<< "Invalid Data"
			<< abort(FatalError);
	}

	if (NOT theInner_) { return; }
	if (theInner_->empty()) return;

	std::vector<std::shared_ptr<Cad_BlockEntity<Pln_Edge>>> blocks;
	theEdges_->RetrieveTo(blocks);

	Debug_If_Condition_Message(blocks.size() NOT_EQUAL 1, "Conflict Data");
	auto block = theEdges_->SelectBlockEntity(blocks[0]->Name());

	Standard_Integer K = 0;
	for (const auto& x : *theInner_)
	{
		Debug_Null_Pointer(x);
		const auto& edges = x->Edges();

		for (const auto& edge : edges)
		{
			Debug_Null_Pointer(edge);
			block->SelectEntity(edge->Index());
		}
		theEdges_->Split("Default Inner Block " + std::to_string(++K));
		block = theEdges_->SelectBlockEntity(blocks[0]->Name());
	}

	theEdges_->UnSelectAll();
	if (NOT block->NbEntities())
	{
		FatalErrorIn("void AutLib::Cad2d_Plane::SplitByWires()")
			<< "Invalid Data"
			<< abort(FatalError);
	}
}

void AutLib::Cad2d_Plane::Make
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
)
{
	Debug_Null_Pointer(theInfo_);
	auto edges = Pln_Edge::MakeEdges(theCurves, Info()->Tolerance());

	for (auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->Approx(Info()->ApproxInfo());
	}

	auto wires =
		Pln_Wire::RetrieveWires(edges);

	CheckWires(wires);

	auto outer =
		RetrieveOuterWire(wires);

	if (wires.size() > 1)
	{
		CheckOuterWire(outer, wires);
	}

	theOuter_ = outer;

	if (wires.size() > 1)
	{
		theInner_ = std::make_shared<wireList>();

		for (const auto& x : wires)
		{
			Debug_Null_Pointer(x);
			if (x NOT_EQUAL outer) theInner_->push_back(x);
		}
	}

	auto Vertices =
		Pln_Edge::RetrieveVertices(edges);

	auto edgeBlock =
		std::make_shared<Cad_BlockEntity<Pln_Edge>>("Default Block Edge", edges);
	theEdges_ = std::make_shared<Cad_EntityManager<Pln_Edge>>(edgeBlock->Name(), edgeBlock);

	auto vertexBlock =
		std::make_shared<Cad_BlockEntity<Pln_Vertex>>("Default Block Vertex", Vertices);
	theVertices_ = std::make_shared<Cad_EntityManager<Pln_Vertex>>(vertexBlock->Name(), vertexBlock);

	SplitByWires();
}

void AutLib::Cad2d_Plane::RetrieveEdgesTo
(
	std::vector<std::shared_ptr<Pln_Edge>>& theEdges
) const
{
	Debug_Null_Pointer(theEdges_);
	theEdges_->RetrieveTo(theEdges);
}

void AutLib::Cad2d_Plane::RetrieveWiresTo
(
	std::vector<std::shared_ptr<Pln_Wire>>& theWires
) const
{
	theWires.push_back(theOuter_);
	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			theWires.push_back(x);
		}
	}
}

const std::shared_ptr<AutLib::Pln_Wire>&
AutLib::Cad2d_Plane::RetrieveOuterWire
(
	const std::vector<std::shared_ptr<Pln_Wire>>& theWires
)
{
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		if (x->Orientation() IS_EQUAL Pln_Orientation_CCW) return x;
	}

	FatalErrorIn("void CheckWires(const wireList& theWires)")
		<< "Found no outer wire!" << endl
		<< abort(FatalError);
	return theWires[0];
}

void AutLib::Cad2d_Plane::CheckOuterWire
(
	const std::shared_ptr<Pln_Wire>& theOuter,
	const std::vector<std::shared_ptr<Pln_Wire>>& theWires
)
{
	if (theWires.size() IS_EQUAL 1)
		return;

	const auto& outer_box = theOuter->BoundingBox();

	std::shared_ptr<Entity2d_Box> box;
	for (const auto& x : theWires)
	{
		if (x NOT_EQUAL theOuter)
		{
			box = x->BoundingBox();
			break;
		}
	}

	for (const auto& x : theWires)
	{
		if (x NOT_EQUAL theOuter)
		{
			*box = Entity2d_Box::Union(*box, *x->BoundingBox());
		}
	}

	if (NOT Entity2d_Box::IsInside(*box, *outer_box))
	{
		FatalErrorIn("void CheckOuterWire(const wire_ptr& theOuter, const wireList& theWires)")
			<< "Invalid outer wire!" << endl
			<< abort(FatalError);
	}
}

void AutLib::Cad2d_Plane::CheckWires
(
	const std::vector<std::shared_ptr<Pln_Wire>>& theWires
)
{
	Standard_Integer K = 0;
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		if (x->Orientation() IS_EQUAL Pln_Orientation_Unknown)
		{
			FatalErrorIn("void CheckWires(const wireList& theWires)")
				<< "Unspecified orientation for the wire!" << endl
				<< abort(FatalError);
		}

		if (x->Orientation() IS_EQUAL Pln_Orientation_CCW) ++K;
	}
	if (NOT K)
	{
		FatalErrorIn("void CheckWires(const wireList& theWires)")
			<< "Found no outer wire!" << endl
			<< abort(FatalError);
	}

	if (K > 1)
	{
		FatalErrorIn("void CheckWires(const wireList& theWires)")
			<< "Found multiple outer wire!" << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<AutLib::Cad2d_Plane> 
AutLib::Cad2d_Plane::MakeBox
(
	const Pnt2d & theCorner,
	const Standard_Real theDx, 
	const Standard_Real theDy
)
{
	auto box = MakeBox(theCorner, theCorner + Pnt2d(theDx, theDy));
	return std::move(box);
}

std::shared_ptr<AutLib::Cad2d_Plane> 
AutLib::Cad2d_Plane::MakeBox
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	const auto& P0 = theP0;
	const auto P1 = Pnt2d(theP1.X(), theP0.Y());
	const auto& P2 = theP1;
	const auto P3 = Pnt2d(theP0.X(), theP1.Y());

	const auto c1 = Cad_Tools::ConvertToBSpline(Cad_Tools::MakeSegment(P0, P1));
	const auto c2 = Cad_Tools::ConvertToBSpline(Cad_Tools::MakeSegment(P1, P2));
	const auto c3 = Cad_Tools::ConvertToBSpline(Cad_Tools::MakeSegment(P2, P3));
	const auto c4 = Cad_Tools::ConvertToBSpline(Cad_Tools::MakeSegment(P3, P0));

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(4);

	curves.push_back
	(
		std::make_shared<Pln_Curve>
		(
			c1->FirstParameter(),
			c1->LastParameter(),
			c1, sysLib::gl_pln_curve_info));

	curves.push_back
	(
		std::make_shared<Pln_Curve>
		(
			c2->FirstParameter(),
			c2->LastParameter(),
			c2, sysLib::gl_pln_curve_info));

	curves.push_back
	(
		std::make_shared<Pln_Curve>
		(
			c3->FirstParameter(),
			c3->LastParameter(),
			c3, sysLib::gl_pln_curve_info));

	curves.push_back
	(
		std::make_shared<Pln_Curve>
		(
			c4->FirstParameter(),
			c4->LastParameter(),
			c4, sysLib::gl_pln_curve_info));

	auto plane = std::make_shared<Cad2d_Plane>(sysLib::gl_plane_info);
	Debug_Null_Pointer(plane);

	plane->Make(curves);

	return std::move(plane);
}