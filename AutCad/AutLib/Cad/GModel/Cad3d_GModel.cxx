#include <Cad3d_GModel.hxx>

#include <GModel_Edge.hxx>
#include <GModel_Curve.hxx>
#include <GModel_parCurve.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Surface.hxx>
#include <GModel_System.hxx>
#include <GModel_FixWireInfo.hxx>

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

	namespace gModel
	{

		static std::shared_ptr<GModel_Edge> GetNewEdge
		(
			Standard_Integer& K,
			const TopoDS_Edge edge,
			const TopoDS_Face theFace
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

			auto curveOnPlane = std::make_shared<GModel_parCurve>(u0, u1, pCurve, gModelSys::par_curve_info);

			std::shared_ptr<GModel_Edge> newEdge;

			++K;

			if (Curve)
			{
				auto curveOnSurface = std::make_shared<GModel_Curve>(U0, U1, Curve, gModelSys::curve_info);
				newEdge = std::make_shared<GModel_Edge>(K, curveOnPlane, curveOnSurface);
			}
			else
			{
				newEdge = std::make_shared<GModel_Edge>(K, curveOnPlane, nullptr);
			}
			return std::move(newEdge);
		}
	}
}

//- Static functions and operators

std::shared_ptr<AutLib::GModel_Surface> 
AutLib::Cad3d_GModel::GetSurface
(
	const TopoDS_Face & theFace
)
{
	const auto forwardFace = TopoDS::Face(theFace.Oriented(TopAbs_FORWARD));

	auto outter_edges_p = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();

	Debug_Null_Pointer(outter_edges_p);
	auto& outter_edges = *outter_edges_p;

	const auto Tol = gModelSys::fix_wire->Tolerance();
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

	SFWF.SetPrecision(gModelSys::fix_wire->Precision());
	SFWF.SetMaxTolerance(gModelSys::fix_wire->MaxTolerance());
	SFWF.SetMinTolerance(gModelSys::fix_wire->MinTolerance());

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
		auto new_edge = gModel::GetNewEdge(K, edge, forwardFace);

		outter_edges.push_back(new_edge);
	}

	auto outerWire = std::make_shared<GModel_Wire>(++wireIndex, outter_edges_p);
	std::shared_ptr<std::vector<std::shared_ptr<GModel_Wire>>> Qwire;
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

		auto Inner_edges_ptr = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();
		auto& Inner_edges = *Inner_edges_ptr;

		ShapeFix_Wire SFWF(wire, forwardFace, Tol);

		SFWF.SetPrecision(gModelSys::fix_wire->Precision());
		SFWF.SetMaxTolerance(gModelSys::fix_wire->MaxTolerance());
		SFWF.SetMinTolerance(gModelSys::fix_wire->MinTolerance());

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

			Inner_edges.push_back(gModel::GetNewEdge(K, edge, forwardFace));
		}

		if (Inner_edges.empty())
		{
			FatalErrorIn("AutLib::Cad3d_SolidTools::face_ptr AutLib::Cad3d_SolidTools::GetSurface(const TopoDS_Face & theFace)")
				<< "Empty wire" << endl
				<< abort(FatalError);
		}

		auto innerWire = std::make_shared<GModel_Wire>(++wireIndex, Inner_edges_ptr);

		if (NOT Qwire) Qwire = std::make_shared<std::vector<std::shared_ptr<GModel_Wire>>>();
		Qwire->push_back(innerWire);
	}

	TopLoc_Location Location;
	auto geometry = BRep_Tool::Surface(forwardFace, Location);

	auto face =
		std::make_shared<GModel_Surface>(geometry, outerWire, Qwire);

	return std::move(face);
}

AutLib::Cad3d_GModel::faceList
AutLib::Cad3d_GModel::GetSurfaces
(
	const TopoDS_Shape & theShape
)
{
	Standard_Integer K = 0;
	faceList list;
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

std::shared_ptr<AutLib::Cad3d_GModel> 
AutLib::Cad3d_GModel::GModel(const TopoDS_Shape & theShape)
{
	auto faces =
		GetSurfaces(theShape);

	auto shape =
		std::make_shared<Cad3d_GModel>(faces);
	return std::move(shape);
}