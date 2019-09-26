#include <GModel_Surface.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Metric1.hxx>
#include <Pnt3d.hxx>
#include <GModel_Wire.hxx>

#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>

Standard_Boolean AutLib::GModel_Surface::IsBSpline() const
{
	return (Standard_Boolean)(Handle(Geom_BSplineSurface)::DownCast(Geometry()));
}

AutLib::Entity2d_Box
AutLib::GModel_Surface::CalcParametricBoundingBox() const
{
	Debug_Null_Pointer(theOuter_);
	auto box = theOuter_->CalcParametricBoundingBox();
	return std::move(box);
}

AutLib::Entity2d_Metric1
AutLib::GModel_Surface::MetricAt
(
	const Pnt2d & theCoord
) const
{
	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	theGeom_->D1(theCoord.X(), theCoord.Y(), Pt, D1U, D1V);

	auto A = D1U.Dot(D1U);
	auto B = D1U.Dot(D1V);
	auto C = D1V.Dot(D1V);

	Entity2d_Metric1 M(A, B, C);
	return std::move(M);
}

AutLib::Pnt3d
AutLib::GModel_Surface::Value
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(theGeom_);
	auto p = theGeom_->Value(theCoord.X(), theCoord.Y());
	return std::move(p);
}

void AutLib::GModel_Surface::GetParametricBouns
(
	Standard_Real & theXmin,
	Standard_Real & theXmax,
	Standard_Real & theYmin,
	Standard_Real & theYmax
) const
{
	const auto& p0 = theBoundingBox_.P0();
	const auto& p1 = theBoundingBox_.P1();

	theXmin = p0.X();
	theXmax = p1.X();

	theYmin = p0.Y();
	theYmax = p1.Y();
}