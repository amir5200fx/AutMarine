#include <AutMarine_Examples.hxx>

#include <Geo_MetricPrcsr_System.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoSizeFun_Uniform.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_System.hxx>
#include <Aft2d_PlnBoundary.hxx>
#include <Aft2d_PlnRegion.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_PlnBoundary.hxx>
#include <Aft_PlnBoundary_System.hxx>
#include <Aft_MetricPrcsr.hxx>


void AutLib::example_boundary_mesh_plane_region()
{
	sysLib::init_pln_approx_curve_info();
	sysLib::init_pln_curve_info();
	sysLib::init_plane_info();

	plnBoundarySys::init_plane_boundary_mesh_info();

	auto b = Cad2d_Plane::MakeBox(Pnt2d(0, 0), Pnt2d(1, 1));

	auto reg = Aft2d_PlnRegion::MakePlane(b);
	
	auto uniSizeFun = std::make_shared<GeoSizeFun_Uniform<Pnt2d>>(0.1, b->BoundingBox());
	
	auto metricMap = 
		std::make_shared<Aft_MetricPrcsr<Aft2d_Edge, Geo2d_SizeFunction>>
		(
			uniSizeFun,
			metricPrcsrSys::metric_processor_integration_info
			);

	auto boundary = std::make_shared<Aft2d_PlnBoundary>(plnBoundarySys::gl_plane_boundary_info);
	boundary->LoadPlane(reg);
	boundary->LoadMetricProcessor(metricMap);

	boundary->Perform();
}