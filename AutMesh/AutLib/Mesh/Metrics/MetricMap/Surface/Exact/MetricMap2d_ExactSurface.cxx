#include <MetricMap2d_ExactSurface.hxx>

#include <Cad_Tools.hxx>
#include <Bnd_Box.hxx>

AutLib::MetricMap2d_ExactSurface::MetricMap2d_ExactSurface
(
	const Handle(Geom_Surface)& thePatch,
	const Entity2d_Box & theBox
)
	: thePatch_(thePatch)
	, MetricMap2d_Surface(theBox)
{}

Standard_Real
AutLib::MetricMap2d_ExactSurface::MaxDim() const
{
	Debug_Null_Pointer(Patch());

	auto box = Cad_Tools::BoundingBox(Patch(), BoundingBox());

	return box.CornerMin().Distance(box.CornerMax());
}

AutLib::MetricMap2d_ExactSurface::metric
AutLib::MetricMap2d_ExactSurface::CalcMetric
(
	const Pnt2d & theCoord,
	const Geom_Surface & theSurface
)
{
	auto u = theCoord.X();
	auto v = theCoord.Y();

	gp_Vec D1U, D1V;
	gp_Pnt Q;
	theSurface.D1(u, v, Q, D1U, D1V);

	auto A = D1U.Dot(D1U);
	auto B = D1U.Dot(D1V);
	auto C = D1V.Dot(D1V);

	metric M(A, B, C);
	return std::move(M);
}

namespace AutLib
{

	static Standard_Real
		CorrectCoordinate
		(
			const Standard_Real x,
			const Standard_Real x0,
			const Standard_Real x1
		)
	{
		Standard_Real xa, xb;
		if (x < x0)
		{
			xa = x1;
			xb = x0;
		}
		else
		{
			xa = x0;
			xb = x1;
		}
		auto dx = xb - xa;
		auto nx = (Standard_Integer)((x - xa) / dx);

		auto delx = (x - xa) - (Standard_Real)nx*dx;

		if (nx % 2) return xb - delx;
		else return xa + delx;
	}
}

AutLib::MetricMap2d_ExactSurface::metric
AutLib::MetricMap2d_ExactSurface::CorrectMetric
(
	const Pnt2d & theCoord,
	const Entity2d_Box & theDomain,
	const Geom_Surface & theSurface
)
{
	if (theDomain.IsInside(theCoord))
	{
		auto m = CalcMetric(theCoord, theSurface);
		return std::move(m);
	}

	const auto& P0 = theDomain.P0();
	const auto& P1 = theDomain.P1();

	const auto x0 = P0.X();
	const auto x1 = P1.X();
	const auto y0 = P0.Y();
	const auto y1 = P1.Y();

	const auto x = theCoord.X();
	const auto y = theCoord.Y();

	auto xc = CorrectCoordinate(x, x0, x1);
	auto yc = CorrectCoordinate(y, y0, y1);

	auto m = CalcMetric(Pnt2d(xc, yc), theSurface);
	return std::move(m);
}