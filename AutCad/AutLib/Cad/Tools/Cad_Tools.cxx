#include <Cad_Tools.hxx>

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Merge_StaticData.hxx>
#include <TecPlot.hxx>

#include <Standard_Handle.hxx>
#include <Bnd_Box.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_AddSurface.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <GeomConvert.hxx>
#include <Geom2dConvert.hxx>
#include <TopLoc_Location.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <STEPControl_Controller.hxx>
#include <STEPControl_Writer.hxx>

std::shared_ptr<AutLib::Entity2d_Triangulation> 
AutLib::Cad_Tools::ParametricTriangulation
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Standard_Integer theNx, 
	const Standard_Integer theNy
)
{
	if (theNx < 2)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	if (theNy < 2)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	const auto Dx = theP1.X() - theP0.X();
	const auto Dy = theP1.Y() - theP0.Y();

	const auto dx = Dx / (Standard_Real)theNx;
	const auto dy = Dy / (Standard_Real)theNy;

	auto tri = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& pts = tri->Points();
	pts.reserve(theNx*theNy);

	auto& indices = tri->Connectivity();
	indices.reserve((theNx - 1)*(theNy - 1)*2);

	Standard_Integer k = 0;
	for (auto i = 0; i < theNx; i++)
	{
		for (auto j = 0; j < theNy; j++)
		{
			auto P0 = theP0 + Pnt2d(i*dx, j*dy);
			/*auto P1 = P0 + Pnt2d(dx, 0);
			auto P2 = P0 + Pnt2d(dx, dy);
			auto P3 = P0 + Pnt2d(0, dy);*/
			//cout << i << ", " << j << "  " << P0 << std::endl;
			pts.push_back(std::move(P0));
		}
	}

	for (auto i = 0; i < theNx - 1; i++)
	{
		for (auto j = 0; j < theNy - 1; j++)
		{
			auto i0 = j * theNx + i + 1;
			auto i1 = j * theNx + i + 2;
			auto i2 = (j + 1)*theNx + i + 2;

			auto j0 = i0;
			auto j1 = i2;
			auto j2 = (j + 1)*theNx + i + 1;

			connectivity::triple I0, I1;
			I0.Value(0) = i0;
			I0.Value(1) = i1;
			I0.Value(2) = i2;

			I1.Value(0) = j0;
			I1.Value(1) = j1;
			I1.Value(2) = j2;

			indices.push_back(std::move(I0));
			indices.push_back(std::move(I1));
		}
	}
	return std::move(tri);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::Triangulation
(
	const Geom_Surface & theSurface, 
	const Entity2d_Triangulation & theParametric
)
{
	const auto& pts0 = theParametric.Points();
	
	auto tri = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& pts = tri->Points();
	pts.reserve(pts.size());

	for (const auto& x : pts0)
	{
		auto pt = theSurface.Value(x.X(), x.Y());
		pts.push_back(std::move(pt));
	}

	tri->Connectivity() = theParametric.Connectivity();

	return std::move(tri);
}

std::shared_ptr<AutLib::Entity3d_Triangulation>
AutLib::Cad_Tools::Triangulation
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Integer theNx,
	const Standard_Integer theNy
)
{
	auto trimmed = Handle(Geom_BoundedSurface)::DownCast(theSurface);
	if (NOT trimmed)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> Triangulation(...)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	Standard_Real U0, U1, V0, V1;
	trimmed->Bounds(U0, U1, V0, V1);

	auto para = 
		ParametricTriangulation(Pnt2d(U0, V0), Pnt2d(U1, V1), theNx, theNy);

	auto tri = Triangulation(*theSurface, *para);

	return std::move(tri);
}

#include <Geom2dAPI_InterCurveCurve.hxx>

std::shared_ptr<Geom2dAPI_InterCurveCurve>
AutLib::Cad_Tools::Intersection
(
	const Handle(Geom2d_Curve)& theCurve0,
	const Handle(Geom2d_Curve)& theCurve1,
	const Standard_Real theTol
)
{
	auto trimmed0 = Handle(Geom2d_BoundedCurve)::DownCast(theCurve0);
	if (NOT trimmed0)
	{
		FatalErrorIn("Handle(Geom2dAPI_InterCurveCurve) Intersection(const Handle(Geom2d_Curve)& theCurve0, const Handle(Geom2d_Curve)& theCurve1, const Standard_Real theTol = 1.0E-6)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto trimmed1 = Handle(Geom2d_BoundedCurve)::DownCast(theCurve1);
	if (NOT trimmed1)
	{
		FatalErrorIn("Handle(Geom2dAPI_InterCurveCurve) Intersection(const Handle(Geom2d_Curve)& theCurve0, const Handle(Geom2d_Curve)& theCurve1, const Standard_Real theTol = 1.0E-6)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto Inter = std::make_shared<Geom2dAPI_InterCurveCurve>(theCurve0, theCurve1, theTol);
	Debug_Null_Pointer(Inter);

	return std::move(Inter);
}

Handle(Geom2d_Curve) 
AutLib::Cad_Tools::ConvertToTrimmedCurve
(
	const Handle(Geom2d_Curve)& theCurve, 
	const Standard_Real theU0, 
	const Standard_Real theU1
)
{
	Handle(Geom2d_Curve) trimmed = 
		new Geom2d_TrimmedCurve(theCurve, theU0, theU1);
	return std::move(trimmed);
}

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
	if (NOT trimmed)
	{
		FatalErrorIn("Handle(Geom_Surface) ConvertToBSpline(const Handle(Geom_Surface)& theSurface)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto bspline = GeomConvert::SurfaceToBSplineSurface(theSurface);
	return std::move(bspline);
}

Handle(Geom2d_Curve) 
AutLib::Cad_Tools::ConvertToBSpline
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	auto trimmed = Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
	if (NOT trimmed)
	{
		FatalErrorIn("Handle(Geom2d_Curve) ConvertToBSpline(const Handle(Geom2d_Curve)& theCurve)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto bspline = Geom2dConvert::CurveToBSplineCurve(theCurve);
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
	if (NOT bspline)
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

std::vector<std::shared_ptr<AutLib::Entity3d_Triangulation>> 
AutLib::Cad_Tools::PreviewUnMergedPatchCurves
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Integer theNbSegments_U,
	const Standard_Integer theNbSegments_V
)
{
	auto bspline = Handle(Geom_BSplineSurface)::DownCast(theSurface);
	if (NOT bspline)
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

	return std::move(trinagulations);
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
AutLib::Cad_Tools::PreviewUnMergedPatchCurves
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

	auto tri = PreviewUnMergedPatchCurves(geom, theNbSegments_U, theNbSegments_V);
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

std::vector<std::shared_ptr<AutLib::Entity3d_Triangulation>> 
AutLib::Cad_Tools::PreviewUnMergedPatchCurves(const TopoDS_Shape& theShape, const Standard_Integer theNbSegments_U, const Standard_Integer theNbSegments_V)
{
	std::vector<std::shared_ptr<Entity3d_Triangulation>> preview;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		auto face = TopoDS::Face(Explorer.Current());

		auto curves = PreviewUnMergedPatchCurves(face, theNbSegments_U, theNbSegments_V);
		for (const auto& x : curves)
		{
			preview.push_back(x);
		}
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
	if (NOT trimmed)
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
	if (NOT trimmed)
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
	return std::move(Triangulation);
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

Bnd_Box2d 
AutLib::Cad_Tools::BoundingBox
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	auto trimmed = Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
	if (NOT trimmed)
	{
		FatalErrorIn("Handle(Geom2d_Curve) ConvertToBSpline(const Handle(Geom2d_Curve)& theCurve)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto box = BoundingBox
	(
		theCurve, 
		trimmed->FirstParameter(),
		trimmed->LastParameter()
	);
	return std::move(box);
}

Bnd_Box2d 
AutLib::Cad_Tools::BoundingBox
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0, 
	const Standard_Real theU1
)
{
	Bnd_Box2d b;
	BndLib_Add2dCurve::Add(theCurve, theU0, theU1, 0, b);

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

void AutLib::Cad_Tools::SplitCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theX,
	Handle(Geom2d_Curve)& theC0, 
	Handle(Geom2d_Curve)& theC1
)
{
	auto trimmed = Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
	if (NOT trimmed)
	{
		FatalErrorIn("void SplitCurve(const Handle(Geom2d_Curve)& theCurve, const Standard_Real theX, Handle(Geom2d_Curve)& theC0, Handle(Geom2d_Curve)& theC1)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	if (NOT INSIDE(theX, theCurve->FirstParameter(), theCurve->LastParameter()))
	{
		FatalErrorIn("void SplitCurve(const Handle(Geom2d_Curve)& theCurve, const Standard_Real theX, Handle(Geom2d_Curve)& theC0, Handle(Geom2d_Curve)& theC1)")
			<< "Invalid Parameter: " << theX << endl
			<< " - First parameter: " << theCurve->FirstParameter() << endl
			<< " - Last parameter: " << theCurve->LastParameter() << endl
			<< abort(FatalError);
	}

	auto first = theCurve->FirstParameter();
	auto last = theCurve->LastParameter();

	theC0 = Cad_Tools::ConvertToTrimmedCurve(theCurve, first, theX);
	theC1 = Cad_Tools::ConvertToTrimmedCurve(theCurve, theX, last);
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

	if (NOT OK)
	{
		FatalErrorIn("void ExportToIGES()")
			<< "Unable to export the model" << endl
			<< abort(FatalError);
	}
}

void AutLib::Cad_Tools::ExportToSTEP
(
	const TopoDS_Shape& theShape,
	const fileName& name
)
{
	STEPControl_Controller::Init();

	STEPControl_Writer Writer;
	Writer.Transfer(theShape, STEPControl_ManifoldSolidBrep);

	Standard_Boolean OK = Writer.Write(name.c_str());

	if (NOT OK)
	{
		FatalErrorIn("void ExportToSTEP()")
			<< "Unable to export the model" << endl
			<< abort(FatalError);
	}
}