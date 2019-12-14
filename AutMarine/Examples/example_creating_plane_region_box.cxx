#include <AutMarine_Examples.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_System.hxx>
#include <Aft2d_PlnBoundary.hxx>
#include <Aft2d_PlnRegion.hxx>
#include <Aft2d_PlnCurve.hxx>

void AutLib::example_creating_plane_region_box()
{
	sysLib::init_pln_approx_curve_info();
	sysLib::init_pln_curve_info();
	sysLib::init_plane_info();

	auto b = Cad2d_Plane::MakeBox(Pnt2d(0, 0), Pnt2d(1, 1));

	auto reg = Aft2d_PlnRegion::MakePlane(b);

	cout << " Has Hole? " << (reg->HasHole() ? "YES" : "NO") << std::endl;
}