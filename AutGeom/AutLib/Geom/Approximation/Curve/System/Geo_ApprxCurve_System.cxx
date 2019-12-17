#include <Geo_ApprxCurve_System.hxx>

#include <Geo_ApprxCurveInfo.hxx>

namespace AutLib
{
	std::shared_ptr<Geo_ApprxCurveInfo> approxCurveSys::gl_approx_curve2d_info =
		std::make_shared<Geo_ApprxCurveInfo>();

	std::shared_ptr<Geo_ApprxCurveInfo> approxCurveSys::gl_approx_curve3d_info =
		std::make_shared<Geo_ApprxCurveInfo>();
}

void AutLib::approxCurveSys::init_approx_curve_info()
{
	auto& info2d = *gl_approx_curve2d_info;
	info2d.SetNbSamples(3);
	info2d.SetInitNbSubdivision(3);
	info2d.SetMaxNbSubdivision(10);
	info2d.SetApprox(0.001);
	info2d.SetAngle(2.0);

	auto& info3d = *gl_approx_curve3d_info;
	info3d.SetNbSamples(5);
	info3d.SetInitNbSubdivision(3);
	info3d.SetMaxNbSubdivision(10);
	info3d.SetApprox(0.001);
	info3d.SetAngle(2.0);
}