#include <AutMarine_Examples.hxx>

#include <Geo_MetricPrcsr_System.hxx>
#include <GeoSizeFun_Uniform.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_System.hxx>
#include <Aft2d_PlnBoundaryAnIso.hxx>
#include <Aft2d_ModelAnIso.hxx>
#include <Aft2d_PlnRegionAnIso.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>
#include <Aft2d_PlnBoundaryAnIso.hxx>
#include <Aft_PlnBoundary_System.hxx>
#include <Aft_MetricPrcsr.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Aft2d_MetricPrcsrAnIso_System.hxx>
#include <Aft2d_ModelAnIso.hxx>
#include <Aft2d_OptNodeAnIso_Calculator.hxx>
#include <Aft2d_CoreAnIso.hxx>
#include <Aft_OptNode.hxx>

void AutLib::example_mesh_aniso_plane()
{
	sysLib::init_pln_approx_curve_info();
	sysLib::init_pln_curve_info();
	sysLib::init_plane_info();

	metricSys::init_aft_metric_prcsr_aniso_info();
	plnBoundarySys::init_plane_boundary_mesh_info();

	fileName name("preview.plt");
	OFstream myFile(name);

	auto b = Cad2d_Plane::MakeBox(Pnt2d(0, 0), Pnt2d(1, 1));

	auto reg = Aft2d_PlnRegionAnIso::MakePlane(b);

	Entity2d_Metric2 M;
	M.SetE1(gp_Dir2d(1.0, 1.0));
	M.SetE2(gp_Dir2d(-1.0, 1.0));
	M.SetH1(0.1);

	auto uniSizeFun = std::make_shared<GeoSizeFun_Uniform<Pnt2d>>(0.1, b->BoundingBox());
	auto uniMetricFun = std::make_shared<GeoMetricFun_Uniform<Pnt2d>>(M, b->BoundingBox());

	auto metricMap =
		std::make_shared<Aft_MetricPrcsr<Aft2d_EdgeAnIso, Geo2d_SizeFunction, Geo2d_MetricFunction>>
		(
			uniSizeFun,
			uniMetricFun,
			metricSys::gl_aft_metric_prcsr_aniso_info
			);

	auto boundary = std::make_shared<Aft2d_PlnBoundaryAnIso>(plnBoundarySys::gl_plane_boundary_aniso_info);
	boundary->LoadPlane(reg);
	boundary->LoadMetricProcessor(metricMap);

	boundary->Perform();

	auto mesher = std::make_shared<Aft_Model<Cad2d_Plane, Geo2d_SizeFunction, Geo2d_MetricFunction>>();
	mesher->LoadBoundaryMetricMap(metricMap);
	mesher->LoadBoundaryEdges(Aft2d_SegmentEdgeAnIso::UpCast(boundary->Boundaries()));

	auto optNode = std::make_shared<Aft_OptNode<Aft2d_EdgeAnIso, Geo2d_SizeFunction, void, false, Geo2d_MetricFunction>>();
	mesher->LoadNodeCalculator(optNode);
	mesher->LoadMetricMap(metricMap);

	mesher->Perform();

	mesher->CreateStaticMesh();
	mesher->StaticMesh()->ExportToPlt(myFile);
}