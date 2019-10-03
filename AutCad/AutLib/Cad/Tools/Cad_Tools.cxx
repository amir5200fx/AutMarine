#include <Cad_Tools.hxx>

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>

#include <Bnd_Box.hxx>
#include <Bnd_Box2d.hxx>
#include <Poly_Triangulation.hxx>

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