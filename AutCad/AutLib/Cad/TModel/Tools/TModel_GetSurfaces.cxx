#include <TModel_Tools.hxx>

#include <TModel_parCurve.hxx>
#include <TModel_Curve.hxx>
#include <TModel_Edge.hxx>
#include <TModel_SingularEdge.hxx>
#include <TModel_Wire.hxx>
#include <TModel_Surface.hxx>
#include <TModel_System.hxx>
#include <TModel_FixWireInfo.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <TopExp_Explorer.hxx>
#include <ShapeFix_Wire.hxx>
#include <BRepTools_WireExplorer.hxx>

namespace AutLib
{

	namespace tModel
	{

		static std::shared_ptr<TModel_Edge> GetNewEdge
		(
			Standard_Integer& K,
			const TopoDS_Edge& edge,
			const TopoDS_Face& theFace
		)
		{
			Standard_Real u0, u1, U0, U1;
			TopLoc_Location pLoc, eLoc;
			auto patch = BRep_Tool::Surface(theFace, pLoc);

			auto pCurve = BRep_Tool::CurveOnSurface(edge, patch, pLoc, u0, u1);
			auto Curve = BRep_Tool::Curve(edge, eLoc, U0, U1);

			if (NOT BRep_Tool::SameRange(edge))
			{
				BRepLib::SameRange(edge);
			}

			if (NOT BRep_Tool::SameParameter(edge))
			{
				FatalErrorIn(FunctionSIG)
					<< "It's supposed that the edge has SameParameter flag" << endl
					<< abort(FatalError);
			}

			if (NOT BRep_Tool::SameRange(edge))
			{
				FatalErrorIn(FunctionSIG)
					<< "It's supposed that the edge has SameRange flag" << endl
					<< abort(FatalError);
			}

			if (edge.Orientation() IS_EQUAL TopAbs_REVERSED)
			{
				auto temp = u1;
				u1 = pCurve->ReversedParameter(u0);
				u0 = pCurve->ReversedParameter(temp);
				pCurve->Reverse();
			}

			auto curveOnPlane = std::make_shared<TModel_parCurve>(u0, u1, pCurve, tModelSys::par_curve_info);

			std::shared_ptr<TModel_Edge> newEdge;

			++K;

			if (Curve)
			{
				auto curveOnSurface = std::make_shared<TModel_Curve>(U0, U1, Curve, tModelSys::curve_info);
				newEdge = std::make_shared<TModel_Edge>(K, curveOnSurface, curveOnPlane);
			}
			else
			{
				newEdge = std::make_shared<TModel_SingularEdge>(K, curveOnPlane);
			}
			return std::move(newEdge);
		}
	}
}

std::shared_ptr<AutLib::TModel_Surface> 
AutLib::TModel_Tools::GetSurface
(
	const TopoDS_Face & theFace
)
{
	const auto forwardFace = TopoDS::Face(theFace.Oriented(TopAbs_FORWARD));

	auto outter_edges_p = std::make_shared<std::vector<std::shared_ptr<TModel_Edge>>>();

	Debug_Null_Pointer(outter_edges_p);
	auto& outter_edges = *outter_edges_p;

	const auto Tol = tModelSys::fix_wire->Tolerance();
	Standard_Integer K = 0;
	Standard_Integer wireIndex = 0;

	const auto outer_wire = BRepTools::OuterWire(forwardFace);

	if (outer_wire.IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "Null outer wire" << endl
			<< abort(FatalError);
	}

	ShapeFix_Wire SFWF(outer_wire, forwardFace, Tol);

	SFWF.SetPrecision(tModelSys::fix_wire->Precision());
	SFWF.SetMaxTolerance(tModelSys::fix_wire->MaxTolerance());
	SFWF.SetMinTolerance(tModelSys::fix_wire->MinTolerance());

	SFWF.FixReorder();
	SFWF.ClosedWireMode() = Standard_True;
	SFWF.FixClosed();
	SFWF.FixConnected();

	SFWF.Perform();

	auto fixed_outer_wire = SFWF.Wire();

	for (
		BRepTools_WireExplorer anEdgeExp(fixed_outer_wire);
		anEdgeExp.More();
		anEdgeExp.Next()
		)
	{
		auto edge = TopoDS::Edge(anEdgeExp.Current());
		auto new_edge = tModel::GetNewEdge(K, edge, forwardFace);

		outter_edges.push_back(new_edge);
	}

	auto outerWire = std::make_shared<TModel_Wire>(++wireIndex, outter_edges_p);
	std::shared_ptr<std::vector<std::shared_ptr<TModel_Wire>>> Qwire;
	for (
		TopExp_Explorer aWireExp(forwardFace, TopAbs_WIRE);
		aWireExp.More();
		aWireExp.Next()
		)
	{
		auto wire = TopoDS::Wire(aWireExp.Current());

		if (wire.IsNull()) continue;
		if (wire IS_EQUAL outer_wire) continue;
		// has inner wire

		auto Inner_edges_ptr = std::make_shared<std::vector<std::shared_ptr<TModel_Edge>>>();
		auto& Inner_edges = *Inner_edges_ptr;

		ShapeFix_Wire SFWF(wire, forwardFace, Tol);

		SFWF.SetPrecision(tModelSys::fix_wire->Precision());
		SFWF.SetMaxTolerance(tModelSys::fix_wire->MaxTolerance());
		SFWF.SetMinTolerance(tModelSys::fix_wire->MinTolerance());

		SFWF.FixReorder();
		SFWF.ClosedWireMode() = Standard_True;
		SFWF.FixClosed();
		SFWF.FixConnected();

		SFWF.Perform();
		wire = SFWF.WireAPIMake();

		for (
			BRepTools_WireExplorer anEdgeExp(wire);
			anEdgeExp.More();
			anEdgeExp.Next()
			)
		{
			auto edge = TopoDS::Edge(anEdgeExp.Current());

			Inner_edges.push_back(tModel::GetNewEdge(K, edge, forwardFace));
		}

		if (Inner_edges.empty())
		{
			FatalErrorIn("AutLib::Cad3d_SolidTools::face_ptr AutLib::Cad3d_SolidTools::GetSurface(const TopoDS_Face & theFace)")
				<< "Empty wire" << endl
				<< abort(FatalError);
		}

		auto innerWire = std::make_shared<TModel_Wire>(++wireIndex, Inner_edges_ptr);

		if (NOT Qwire) Qwire = std::make_shared<std::vector<std::shared_ptr<TModel_Wire>>>();
		Qwire->push_back(innerWire);
	}

	TopLoc_Location Location;
	auto geometry = BRep_Tool::Surface(forwardFace, Location);

	auto face =
		std::make_shared<TModel_Surface>(geometry, outerWire, Qwire);
	face->SetFace(theFace);

	return std::move(face);
}

std::vector<std::shared_ptr<AutLib::TModel_Surface>> 
AutLib::TModel_Tools::GetSurfaces
(
	const TopoDS_Shape & theShape
)
{
	Standard_Integer K = 0;
	std::vector<std::shared_ptr<TModel_Surface>> list;
	for (
		TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto raw = TopoDS::Face(aFaceExp.Current());

		TopLoc_Location aLoc;
		auto tri = BRep_Tool::Triangulation(raw, aLoc);
		if (tri)
		{
			auto trans = aLoc.Transformation();

			auto& pts = tri->ChangeNodes();
			forThose(Index, 1, pts.Size())
			{
				auto& p = pts.ChangeValue(Index);
				p.Transform(trans);
			}
		}

		if (raw.IsNull())
		{
			continue;
		}

		auto face = GetSurface(raw);

		face->SetIndex(++K);

		if (tri)
		{
			face->SetTriangulation(tri);
		}

		list.push_back(face);
	}

	return std::move(list);
}