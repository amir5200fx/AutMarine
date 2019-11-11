#include <CadPlnModel_Curve.hxx>

#include <Geo2d_ApprxCurve.hxx>
#include <Pln_Curve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

std::shared_ptr<AutLib::Pln_Curve> 
AutLib::CadPlnModel_Curve::Curve() const
{
	auto curve = std::dynamic_pointer_cast<Pln_Curve>(Entity());
	return std::move(curve);
}

AutLib::Pnt2d 
AutLib::CadPlnModel_Curve::P0() const
{
	auto curve = Curve();
	auto pt = curve->FirstCoord();

	return std::move(pt);
}

AutLib::Pnt2d 
AutLib::CadPlnModel_Curve::P1() const
{
	auto curve = Curve();
	auto pt = curve->LastCoord();

	return std::move(pt);
}

void AutLib::CadPlnModel_Curve::Discrete
(
	const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
) const
{
	const auto& curve = Curve();

	Geo2d_ApprxCurve approx(curve->Curve(), curve->FirstParam(), curve->LastParam(), theInfo);
	approx.Perform();

	if (NOT approx.IsDone())
	{
		FatalErrorIn("void Discrete(const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo) const")
			<< "the algorithm has not been performed!" << endl
			<< abort(FatalError);
	}

	ChangeMesh() = approx.Chain();
}