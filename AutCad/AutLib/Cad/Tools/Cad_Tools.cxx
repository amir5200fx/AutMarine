#include <Cad_Tools.hxx>

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>

#include <Bnd_Box.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_AddSurface.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <TopLoc_Location.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>

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