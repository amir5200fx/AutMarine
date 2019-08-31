#include <Cad_Tools.hxx>

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>

#include <Bnd_Box.hxx>
#include <Bnd_Box2d.hxx>

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