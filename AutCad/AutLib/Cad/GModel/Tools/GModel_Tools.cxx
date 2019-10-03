#include <GModel_Tools.hxx>

#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <GModel_parCurve.hxx>
#include <GModel_Curve.hxx>

std::shared_ptr<AutLib::Entity2d_Polygon>
AutLib::GModel_Tools::UniformDiscrete
(
	const GModel_parCurve & theCurve,
	const Standard_Integer theNbSegments
)
{
	auto nbSeg = MIN(theNbSegments, 3);

	auto poly = std::make_shared<Entity2d_Polygon>();
	auto& pts = poly->Points();

	pts.reserve(nbSeg + 1);
	auto du = (theCurve.LastParam() - theCurve.FirstParam()) / (Standard_Real)nbSeg;
	auto u0 = theCurve.FirstParam();

	forThose(Index, 0, nbSeg)
	{
		auto u = Index * du + u0;
		pts.push_back(theCurve.Value(u));
	}

	return std::move(poly);
}

std::shared_ptr<AutLib::Entity3d_Polygon>
AutLib::GModel_Tools::UniformDiscrete
(
	const GModel_Curve& theCurve,
	const Standard_Integer theNbSegments
)
{
	auto nbSeg = MIN(theNbSegments, 3);

	auto poly = std::make_shared<Entity3d_Polygon>();
	auto& pts = poly->Points();

	pts.reserve(nbSeg + 1);
	auto du = (theCurve.LastParam() - theCurve.FirstParam()) / (Standard_Real)nbSeg;
	auto u0 = theCurve.FirstParam();

	forThose(Index, 0, nbSeg)
	{
		auto u = Index * du + u0;
		pts.push_back(theCurve.Value(u));
	}

	return std::move(poly);
}