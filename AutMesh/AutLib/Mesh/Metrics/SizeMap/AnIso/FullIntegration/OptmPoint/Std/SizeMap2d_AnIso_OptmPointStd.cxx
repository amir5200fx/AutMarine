#include <SizeMap2d_AnIso_OptmPointStd.hxx>

#include <Aft2d_EdgeAnIso.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>

#include <armadillo.h>

using namespace arma;

const Standard_Real AutLib::SizeMap2d_AnIso_OptmPointStd::C3(1.7320508075688773);

void AutLib::SizeMap2d_AnIso_OptmPointStd::Perform()
{
	const auto h = ElementSize();
	const auto invH2 = (Standard_Real)1.0 / (h*h);

	const auto& edge = Front();
	const auto& centre = edge.Centre();

	Debug_Null_Pointer(edge.Node0());
	Debug_Null_Pointer(edge.Node1());
	const auto& v0 = edge.Node0()->Coord();
	const auto& v1 = edge.Node1()->Coord();

	const auto& anIsoMap = SizeMap();

	Debug_Null_Pointer(anIsoMap.MetricMap());
	const auto& metricMap = *anIsoMap.MetricMap();

	auto& CurrentMetric = anIsoMap.CurrentMetric;
	CurrentMetric = metricMap.MetricAt(centre);

	Entity2d_Metric1 M(invH2*CurrentMetric.A(), invH2*CurrentMetric.B(), invH2*CurrentMetric.C());
	const auto D = sqrt(M.Determinant());
	//const auto cte = C3 / (2.0*D*anIsoMap.CalcDistance(centre, v1));
	const auto cte = C3 / (2.0*D*Entity2d_Metric1::Distance(centre, v1, CurrentMetric));

	auto dU = v1 - centre;

	vec2 U;
	U(0) = dU.X();
	U(1) = dU.Y();

	mat22 orthM;
	orthM(0, 0) = 0;// -M.B();
	orthM(0, 1) = -M.C();
	orthM(1, 0) = M.A();
	orthM(1, 1) = 0;// M.B();

	U = cte * (orthM*U);

	Pnt2d P(centre.X() + U(0), centre.Y() + U(1));
	//cout << "distance = " << anIsoMap.CalcDistance(centre, P) << std::endl;
	theCoord_ = std::move(P);
	Change_IsDone() = Standard_True;
}
