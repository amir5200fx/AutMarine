#include <Cad_Tools.hxx>

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Merge_StaticData.hxx>

#include <Bnd_Box.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_AddSurface.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <GeomConvert.hxx>
#include <TopLoc_Location.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>

Handle(Geom_Surface)
AutLib::Cad_Tools::ConvertToRectangularTrimmedSurface
(
	const Handle(Geom_Surface)& theSurface,
	const Entity2d_Box& theBoundaries
)
{
	auto u1 = theBoundaries.P0().X();
	auto u2 = theBoundaries.P1().X();
	auto v1 = theBoundaries.P0().Y();
	auto v2 = theBoundaries.P1().Y();

	Handle(Geom_Surface) trimmed = 
		new Geom_RectangularTrimmedSurface(theSurface, u1, u2, v1, v2);
	return std::move(trimmed);
}

Handle(Geom_Surface)
AutLib::Cad_Tools::ConvertToBSpline
(
	const Handle(Geom_Surface)& theSurface
)
{
	auto trimmed = Handle(Geom_BoundedSurface)::DownCast(theSurface);
	if (not trimmed)
	{
		FatalErrorIn("Handle(Geom_Surface) ConvertToBSpline(const Handle(Geom_Surface)& theSurface)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto bspline = GeomConvert::SurfaceToBSplineSurface(theSurface);
	return std::move(bspline);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::PreviewPatchCurves
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Integer theNbSegments_U,
	const Standard_Integer theNbSegments_V
)
{
	auto bspline = Handle(Geom_BSplineSurface)::DownCast(theSurface);
	if (not bspline)
	{
		FatalErrorIn("Handle(Geom_Surface) PreviewPatchCurves(const Handle(Geom_Surface)& theSurface)")
			<< "Invalid Data: the surface is not bspline!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto uknots = bspline->UKnots();
	auto vknots = bspline->VKnots();

	std::vector<std::shared_ptr<Entity3d_Triangulation>> trinagulations;
	trinagulations.reserve(uknots.Size() + vknots.Size());

	for (const auto x : uknots)
	{
		auto tr = PreviewCurveOnSurface_U(theSurface, x, theNbSegments_U);
		trinagulations.push_back(std::move(tr));
	}

	for (const auto x : vknots)
	{
		auto tr = PreviewCurveOnSurface_V(theSurface, x, theNbSegments_U);
		trinagulations.push_back(std::move(tr));
	}

	Merge_StaticData<Entity3d_Triangulation> merge;
	merge.Import(trinagulations);

	merge.Perform();
	if (NOT merge.IsDone())
	{
		FatalErrorIn("Handle(Geom_Surface) PreviewPatchCurves(const Handle(Geom_Surface)& theSurface)")
			<< " the merge algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	auto merged = merge.Merged();

	return std::move(merged);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::PreviewPatchCurves
(
	const TopoDS_Face& theFace,
	const Standard_Integer theNbSegments_U,
	const Standard_Integer theNbSegments_V
)
{
	auto geom = BRep_Tool::Surface(theFace);
	if (NOT geom)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> PreviewPatchCurves()")
			<< "the face has no geometry!" << endl
			<< abort(FatalError);
	}

	auto tri = PreviewPatchCurves(geom, theNbSegments_U, theNbSegments_V);
	return std::move(tri);
}

std::vector<std::shared_ptr<AutLib::Entity3d_Triangulation>>
AutLib::Cad_Tools::PreviewPatchCurves
(
	const TopoDS_Shape& theShape, 
	const Standard_Integer theNbSegments_U, 
	const Standard_Integer theNbSegments_V
)
{
	std::vector<std::shared_ptr<Entity3d_Triangulation>> preview;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		preview.push_back(PreviewPatchCurves(TopoDS::Face(Explorer.Current()), theNbSegments_U, theNbSegments_V));
	}
	return std::move(preview);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::PreviewCurveOnSurface_U
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Real u,
	const Standard_Integer theNbSegments
)
{
	auto trimmed = Handle(Geom_BoundedSurface)::DownCast(theSurface);
	if (not trimmed)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> PreviewCurveOnSurface_U(...)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	Standard_Real u0, u1, v0, v1;
	theSurface->Bounds(u0, u1, v0, v1);

	auto triangulation = std::make_shared<Entity3d_Triangulation>();
	auto& pts = triangulation->Points();

	auto nbsegts = MAX(theNbSegments, 3);
	auto dv = (v1 - v0) / (Standard_Real)nbsegts;

	pts.reserve(nbsegts + 1);
	forThose(Index, 0, nbsegts)
	{
		auto v = Index * dv + v0;
		auto pt = theSurface->Value(u, v);

		pts.push_back(std::move(pt));
	}

	auto& indices = triangulation->Connectivity();
	indices.reserve(nbsegts);
	forThose(Index, 0, nbsegts - 1)
	{
		connectivity::triple t;
		t.Value(0) = Index + 1;
		t.Value(1) = Index + 2;
		t.Value(2) = Index + 1;

		indices.push_back(std::move(t));
	}

	return std::move(triangulation);
}

std::shared_ptr<AutLib::Entity3d_Triangulation>
AutLib::Cad_Tools::PreviewCurveOnSurface_V
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Real v,
	const Standard_Integer theNbSegments
)
{
	auto trimmed = Handle(Geom_BoundedSurface)::DownCast(theSurface);
	if (not trimmed)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> PreviewCurveOnSurface_V(...)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	Standard_Real u0, u1, v0, v1;
	theSurface->Bounds(u0, u1, v0, v1);

	auto triangulation = std::make_shared<Entity3d_Triangulation>();
	auto& pts = triangulation->Points();

	auto nbsegts = MAX(theNbSegments, 3);
	auto du = (u1 - u0) / (Standard_Real)nbsegts;

	pts.reserve(nbsegts + 1);
	forThose(Index, 0, nbsegts)
	{
		auto u = Index * du + u0;
		auto pt = theSurface->Value(u, v);

		pts.push_back(std::move(pt));
	}

	auto& indices = triangulation->Connectivity();
	indices.reserve(nbsegts);
	forThose(Index, 0, nbsegts - 1)
	{
		connectivity::triple t;
		t.Value(0) = Index + 1;
		t.Value(1) = Index + 2;
		t.Value(2) = Index + 1;

		indices.push_back(std::move(t));
	}

	return std::move(triangulation);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::PreviewCurve
(
	const Handle(Geom_Curve)& theCurve,
	const Standard_Integer theNbSegments
)
{
	auto bounded = Handle(Geom_BoundedCurve)::DownCast(theCurve);
	if (NOT bounded)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity3d_Triangulation> PreviewPatchCurves(const Handle(Geom_Surface)& theSurface)")
			<< " invalid Data: the curve is not bounded!" << endl
			<< " - first, convert the it to a trimmed one" << endl
			<< abort(FatalError);
	}

	auto triangulation = std::make_shared<Entity3d_Triangulation>();
	auto& pts = triangulation->Points();
	
	auto nbsegts = MAX(theNbSegments, 3);
	auto u0 = theCurve->FirstParameter();
	auto u1 = theCurve->LastParameter();
	auto du = (u1 - u0) / (Standard_Real)nbsegts;

	pts.reserve(nbsegts + 1);
	forThose(Index, 0, nbsegts)
	{
		auto u = Index * du + u0;
		auto pt = theCurve->Value(u);

		pts.push_back(std::move(pt));
	}

	auto& indices = triangulation->Connectivity();
	indices.reserve(nbsegts);
	forThose(Index, 0, nbsegts - 1)
	{
		connectivity::triple t;
		t.Value(0) = Index + 1;
		t.Value(1) = Index + 2;
		t.Value(2) = Index + 1;

		indices.push_back(std::move(t));
	}

	return std::move(triangulation);
}

AutLib::Entity2d_Box 
AutLib::Cad_Tools::BoundingBox
(
	const Bnd_Box2d & theBox
)
{
	Standard_Real Xmin, Xmax;
	Standard_Real Ymin, Ymax;

	theBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}

AutLib::Entity3d_Box 
AutLib::Cad_Tools::BoundingBox
(
	const Bnd_Box & theBox
)
{
	Standard_Real Xmin, Xmax;
	Standard_Real Ymin, Ymax;
	Standard_Real Zmin, Zmax;

	theBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	Entity3d_Box box(Pnt3d(Xmin, Ymin, Zmin), Pnt3d(Xmax, Ymax, Zmin));
	return std::move(box);
}

Handle(Poly_Triangulation) 
AutLib::Cad_Tools::RetrieveTriangulation
(
	const TopoDS_Face & theFace
)
{
	TopLoc_Location Loc;
	auto Triangulation = BRep_Tool::Triangulation(theFace, Loc);

	return Triangulation;
}

std::vector<Handle(Poly_Triangulation)> 
AutLib::Cad_Tools::RetrieveTriangulation
(
	const TopoDS_Shape & theShape
)
{
	std::vector<Handle(Poly_Triangulation)> tris;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		tris.push_back(RetrieveTriangulation(TopoDS::Face(Explorer.Current())));
	}
	return std::move(tris);
}

Bnd_Box 
AutLib::Cad_Tools::BoundingBox
(
	const Handle(Geom_Surface)& theSurface, 
	const Entity2d_Box & theParams
)
{
	const auto& P0 = theParams.P0();
	const auto& P1 = theParams.P1();

	GeomAdaptor_Surface adaptor(theSurface, P0.X(), P1.X(), P0.Y(), P1.Y());

	Bnd_Box b;
	BndLib_AddSurface::Add(adaptor, 0, b);

	return std::move(b);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::Triangulation
(
	const Poly_Triangulation & theTriangulation
)
{
	auto triangulation = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(triangulation);

	auto& pts = triangulation->Points();
	auto& indices = triangulation->Connectivity();

	pts.reserve(theTriangulation.NbNodes());
	for (const auto& x : theTriangulation.Nodes())
	{
		pts.push_back(x);
	}

	indices.reserve(theTriangulation.NbTriangles());
	for (const auto& x : theTriangulation.Triangles())
	{
		Standard_Integer i0, i1, i2;
		x.Get(i0, i1, i2);

		connectivity::triple I;
		I.Value(0) = i0;
		I.Value(1) = i1;
		I.Value(2) = i2;

		indices.push_back(std::move(I));
	}
	return std::move(triangulation);
}

void AutLib::Cad_Tools::ExportToIGES
(
	const word & unit,
	const TopoDS_Shape & theShape,
	const fileName & name
)
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer(unit.c_str(), 0);
	Writer.AddShape(theShape);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write(name.c_str());
}