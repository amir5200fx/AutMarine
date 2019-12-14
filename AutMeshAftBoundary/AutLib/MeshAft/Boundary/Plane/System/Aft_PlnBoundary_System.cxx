#include <Aft_PlnBoundary_System.hxx>

#include <Numeric_NewtonSolverInfo.hxx>
#include <Numeric_AdaptIntegrationInfo.hxx>
#include <Mesh_CurveOptmPoint_CorrectionInfo.hxx>
#include <Mesh_CurveInfo.hxx>
#include <Aft2d_PlnBoundary_Info.hxx>
#include <Aft2d_MetricPrcsrAnIso_System.hxx>

namespace AutLib
{
	std::shared_ptr<Numeric_AdaptIntegrationInfo> plnBoundarySys::gl_plane_boundary_intg_overall_info =
		std::make_shared<Numeric_AdaptIntegrationInfo>();

	std::shared_ptr<Numeric_AdaptIntegrationInfo> plnBoundarySys::gl_plane_boundary_intg_newton_info =
		std::make_shared<Numeric_AdaptIntegrationInfo>();

	std::shared_ptr<Numeric_NewtonSolverInfo> plnBoundarySys::gl_plane_boundary_newton_solver_info =
		std::make_shared<Numeric_NewtonSolverInfo>();

	std::shared_ptr<Mesh_CurveOptmPoint_CorrectionInfo> plnBoundarySys::gl_plane_boundary_opt_node_info =
		std::make_shared<Mesh_CurveOptmPoint_CorrectionInfo>();

	std::shared_ptr<Mesh_CurveInfo> plnBoundarySys::gl_plane_boundary_curve_mesh_info =
		std::make_shared<Mesh_CurveInfo>();

	std::shared_ptr<Aft2d_PlnBoundary_Info> plnBoundarySys::gl_plane_boundary_info =
		std::make_shared<Aft2d_PlnBoundary_Info>();


}

void AutLib::plnBoundarySys::init_plane_boundary_mesh_info()
{
	auto& intgOverallInfo = *gl_plane_boundary_intg_overall_info;
	intgOverallInfo.SetMaxNbIterations(500);
	intgOverallInfo.SetNbInitIterations(10);
	intgOverallInfo.SetTolerance(1.0E-8);
	
	auto& intgNewtonInfo = *gl_plane_boundary_intg_newton_info;
	intgNewtonInfo.SetMaxNbIterations(150);
	intgNewtonInfo.SetNbInitIterations(3);
	intgNewtonInfo.SetTolerance(1.0E-4);

	auto& newtonSolver = *gl_plane_boundary_newton_solver_info;
	newtonSolver.SetTolerance(1.0E-6);
	newtonSolver.SetUnderRelaxation(0.8);
	newtonSolver.MaxNbIterations() = 100;

	auto& optNode = *gl_plane_boundary_opt_node_info;
	optNode.SetMaxLevel(8);
	optNode.SetTolerance(1.0E-6);
	optNode.SetUnderRelaxation(0.85);

	auto& curveMesh = *gl_plane_boundary_curve_mesh_info;
	curveMesh.SetLengthCalcMaxLevel(15);
	curveMesh.SetUnderRelaxation(0.85);

	curveMesh.OverrideOverallLengthIntgInfo(gl_plane_boundary_intg_overall_info);
	curveMesh.OverrideNewtonIntgInfo(gl_plane_boundary_intg_newton_info);
	curveMesh.OverrideNewtonIterInfo(gl_plane_boundary_newton_solver_info);
	curveMesh.OverrideCorrAlgInfo(gl_plane_boundary_opt_node_info);

	auto& plan = *gl_plane_boundary_info;
	plan.OverrideGlobalCurve(gl_plane_boundary_curve_mesh_info);
	plan.SetMergeTolerance(1.0E-4);
	
}