#include <Cad2d_Plane_System.hxx>

#include <Cad_CurveInfo.hxx>
#include <Cad2d_PlaneInfo.hxx>

namespace AutLib
{
	std::shared_ptr<Geo_ApprxCurveInfo> sysLib::gl_pln_approx_curve_info = std::make_shared<Geo_ApprxCurveInfo>();
	std::shared_ptr<Cad_CurveInfo> sysLib::gl_pln_curve_info = std::make_shared<Cad_CurveInfo>();

	std::shared_ptr<Cad2d_PlaneInfo> sysLib::gl_plane_info = std::make_shared<Cad2d_PlaneInfo>();
}

void AutLib::sysLib::init_pln_curve_info()
{
	auto& info = *gl_pln_curve_info;
	info.SetNbDivisions(20);
}

void AutLib::sysLib::init_pln_approx_curve_info()
{
	auto info = *gl_pln_approx_curve_info;
	info.SetAngle(2.0);
	info.SetApprox(0.05);
}

void AutLib::sysLib::init_plane_info()
{
	auto& info = *gl_plane_info;
	info.OverrideApproxInfo(gl_pln_approx_curve_info);
}