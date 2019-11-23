#include <Cad2d_Plane_System.hxx>

#include <Cad_CurveInfo.hxx>

namespace AutLib
{
	std::shared_ptr<Cad_CurveInfo> sysLib::gl_pln_curve_info = std::make_shared<Cad_CurveInfo>();
}

void AutLib::sysLib::init_pln_curve_info()
{
	auto& info = *gl_pln_curve_info;
	info.SetNbDivisions(20);
}