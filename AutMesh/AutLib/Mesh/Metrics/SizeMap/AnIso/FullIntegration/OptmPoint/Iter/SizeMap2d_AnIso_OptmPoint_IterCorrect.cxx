#include <SizeMap2d_AnIso_OptmPoint_IterCorrect.hxx>

#include <Aft2d_EdgeAnIso.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>

#include <armadillo.h>

using namespace arma;

void AutLib::SizeMap2d_AnIso_OptmPoint_IterCorrect::Perform()
{
	ChangeCoord() = P0();

	const auto& anIsoMap = SizeMap();

	Debug_Null_Pointer(anIsoMap.MetricMap());
	const auto& metricMap = *anIsoMap.MetricMap();

	const auto omega = Info()->UnderRelaxation();
	const auto conv = Info()->Tolerance();

	const auto& edge = Front();

	Debug_Null_Pointer(edge.Node0());
	Debug_Null_Pointer(edge.Node1());
	const auto& v0 = edge.Node0()->Coord();
	const auto& v1 = edge.Node1()->Coord();

	auto P = P0();

	Standard_Integer Iter = 0;
	do
	{
		auto d0 = anIsoMap.CalcUnitDistance(v0, P);
		auto d1 = anIsoMap.CalcUnitDistance(v1, P);

		Debug_If_Condition(d0 <= gp::Resolution());
		Debug_If_Condition(d1 <= gp::Resolution());

		auto Pa = v0 + (P - v0) / d0;
		auto Pb = v1 + (P - v1) / d1;

		auto Pn = 0.5*(Pa + Pb);
		auto dP = Pn - P;

		P += omega * dP;

		if (ABS(1.0 - d0) <= conv AND ABS(1.0 - d1) <= conv)
		{
			ChangeConverged() = Standard_True;
			break;
		}
	} while (++Iter <= Info()->MaxNbIterations());

	ChangeCoord() = std::move(P);
	Change_IsDone() = Standard_True;
}