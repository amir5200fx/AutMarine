#include <Mesh2d_OptNodeAnIso_Analytical.hxx>

#include <armadillo.h>

using namespace arma;

const Standard_Real AutLib::Mesh2d_OptNodeAnIso_Analytical_Base::C3(1.7320508075688773);

AutLib::Pnt2d 
AutLib::Mesh2d_OptNodeAnIso_Analytical_Base::CalcCoord
(
	const Standard_Real theSize,
	const Aft2d_EdgeAnIso & theEdge,
	const Entity2d_Metric1 & theMetric
)
{
	const auto invH2 = (Standard_Real)1.0 / (theSize*theSize);

	const auto& centre = theEdge.Centre();

	Debug_Null_Pointer(theEdge.Node0());
	Debug_Null_Pointer(theEdge.Node1());

	const auto& v0 = theEdge.Node0()->Coord();
	const auto& v1 = theEdge.Node1()->Coord();

	const auto D = sqrt(theMetric.Determinant());
	const auto cte = C3 / (2.0*D*Entity2d_Metric1::Distance(centre, v1, theMetric));

	auto dU = v1 - centre;

	vec2 U;
	U(0) = dU.X();
	U(1) = dU.Y();

	mat22 orthM;
	orthM(0, 0) = -theMetric.B();
	orthM(0, 1) = -theMetric.C();
	orthM(1, 0) = theMetric.A();
	orthM(1, 1) = theMetric.B();

	U = cte * (orthM*U);

	Pnt2d P(centre.X() + U(0), centre.Y() + U(1));

	return std::move(P);
}