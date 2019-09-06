#include <SizeMap2d_FullIntAnIso.hxx>

#include <Entity2d_Eigen.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <Mesh_LineIntegrand.hxx>
#include <Mesh_LineIntegrand_Function.hxx>
#include <SizeMap2d_FullIntAnIsoInfo.hxx>

Standard_Real AutLib::SizeMap2d_FullIntAnIso::DimSize() const
{
	Debug_Null_Pointer(MetricMap());
	return MetricMap()->BoundingBox().Diameter();
}

AutLib::Pnt2d
AutLib::SizeMap2d_FullIntAnIso::CorrEffRegion
(
	const Pnt2d & theCentre,
	const Pnt2d & theP,
	const Standard_Real theRadius
) const
{
	static const Standard_Integer nbIters = 4;
	static const Standard_Real Tol = 0.005;
	auto P = theP;
	forThose(Iter, 1, nbIters)
	{
		auto d = CalcDistance(theCentre, P) / theRadius;
		P = theCentre + (1.0 / d)*(P - theCentre);

		if (d <= Tol)
		{
			break;
		}
	}
	return std::move(P);
}

Standard_Real
AutLib::SizeMap2d_FullIntAnIso::CalcDistance
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
) const
{
	Mesh_LineIntegrand_FullIntAnIso line(theP0, theP1, *this);

	Mesh_LineIntegrand_Function_FullIntAnIso func(line);

	Debug_Null_Pointer(Info());
	auto& info = *Info()->AdaptIntgInfo();

	Numeric_AdaptIntegration_FullIntAnIso Integration(func, 0, 1, info);
	Integration.Perform();

	Debug_If_Condition_Message(NOT info.IsDone(), "Integration has not been performed");

	if (NOT info.IsConverged())
	{
		IterFailedIn(FunctionSIG, info.NbInitIterations())
			<< "Algorithm is not converged!" << endl
			<< abort(IterFail);
	}
	return info.Result();
}

Standard_Real
AutLib::SizeMap2d_FullIntAnIso::CalcUnitDistance
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
) const
{
	Mesh_LineIntegrand_FullIntAnIso line(theP0, theP1, *this);

	Mesh_LineIntegrand_UnitLengthFunction_FullIntAnIso func(line);

	Debug_Null_Pointer(Info());
	auto& info = *Info()->AdaptIntgInfo();

	Numeric_AdaptIntegration_UnitLengthFullIntAnIso Integration(func, 0, 1, info);
	Integration.Perform();

	Debug_If_Condition_Message(NOT info.IsDone(), "Integration has not been performed");

	if (NOT info.IsConverged())
	{
		IterFailedIn(FunctionSIG, info.NbInitIterations())
			<< "Algorithm is not converged!" << endl
			<< abort(IterFail);
	}
	return info.Result();
}

#include <SizeMap2d_AnIso_OptmPointStd.hxx>
#include <SizeMap2d_AnIso_OptmPoint_IterCorrect.hxx>
#include <Entity2d_Eigen.hxx>

AutLib::Pnt2d
AutLib::SizeMap2d_FullIntAnIso::CalcOptimumCoord
(
	const Standard_Real theSize,
	const front & theEdge
) const
{
	SizeMap2d_AnIso_OptmPointStd IntP(theSize, BoundingBox(), theEdge, *this);
	IntP.Perform();

	Debug_If_Condition_Message
	(
		NOT IntP.IsDone(),
		"the SizeMap2d_AnIso_OptmPointStd algorithm has not been performed");
	const auto& P0 = IntP.Coord();
	//return IntP.Coord();
	SizeMap2d_AnIso_OptmPoint_IterCorrect
		IterCorrt
		(
			theSize, BoundingBox(),
			theEdge, *this, P0, Info()->IterCorrInfo());

	IterCorrt.Perform();
	Debug_If_Condition_Message
	(
		NOT IterCorrt.IsDone(),
		"the SizeMap2d_AnIso_OptmPoint_IterCorrect algorithm has not been performed");

	auto P = IterCorrt.Coord();

	return std::move(P);
}

AutLib::SizeMap2d_FullIntAnIso::box
AutLib::SizeMap2d_FullIntAnIso::CalcSearchRegion
(
	const Standard_Real theRadius,
	const metric & theMetric,
	const Pnt2d & theCentre
) const
{
	Debug_Null_Pointer(size_map2d_full_aniso_adapt_eigen);
	auto& eigen = *size_map2d_full_aniso_adapt_eigen;

	auto c = 1.0 / (theRadius*theRadius);
	eigen.CalcEigen(c*theMetric);

	auto dQd = eigen.H2()*eigen.E2();
	auto dQr = eigen.H1()*eigen.E1();

	auto Qd = theCentre - dQd;
	auto Qu = theCentre + dQd;

	std::vector<Pnt2d> Pts(4);
	Pts[0] = Qd + dQr;
	Pts[1] = Qu + dQr;
	Pts[2] = Qu - dQr;
	Pts[3] = Qd - dQr;

	auto box = Entity2d_Box::BoundingBoxOf(Pts);
	return std::move(box);
}

AutLib::SizeMap2d_FullIntAnIso::box
AutLib::SizeMap2d_FullIntAnIso::CalcSearchRegion
(
	const Standard_Real theRadius,
	const Pnt2d & theCentre,
	const front & theEdge
) const
{
	auto mp =
		CalcEffectiveMetric(theEdge.Centre(), theCentre);

	const auto& n0 = *theEdge.Node0();
	const auto& n1 = *theEdge.Node1();

	const auto& m0 = n0.Metric();
	const auto& m1 = n1.Metric();

	auto m = Entity2d_Metric1::UnionSR(mp, Entity2d_Metric1::UnionSR(m0, m1));
	m *= (1.0 / (theRadius*theRadius));

	Debug_Null_Pointer(size_map2d_full_aniso_adapt_eigen);
	auto& eigen = *size_map2d_full_aniso_adapt_eigen;

	eigen.CalcEigen(m);

	auto dQd = eigen.H2()*eigen.E2();
	auto dQr = eigen.H1()*eigen.E1();

	auto Qd = theCentre - dQd;
	auto Qu = theCentre + dQd;

	std::vector<Pnt2d> Pts(4);
	Pts[0] = Qd + dQr;
	Pts[1] = Qu + dQr;
	Pts[2] = Qu - dQr;
	Pts[3] = Qd - dQr;

	auto box = Entity2d_Box::BoundingBoxOf(Pts);
	return std::move(box);
}

AutLib::SizeMap2d_FullIntAnIso::box
AutLib::SizeMap2d_FullIntAnIso::CalcSearchRegion
(
	const Standard_Real theRadius,
	const front & theEdge
) const
{
	const auto& n0 = *theEdge.Node0();
	const auto& n1 = *theEdge.Node1();

	const auto& m0 = n0.Metric();
	const auto& m1 = n1.Metric();

	auto m = Entity2d_Metric1::UnionSR(m0, m1);
	m *= (1.0 / (theRadius*theRadius));

	Debug_Null_Pointer(size_map2d_full_aniso_adapt_eigen);
	auto& eigen = *size_map2d_full_aniso_adapt_eigen;

	eigen.CalcEigen(m);

	auto dQd = eigen.H2()*eigen.E2();
	auto dQr = eigen.H1()*eigen.E1();

	const auto& centre = theEdge.Centre();

	auto Qd = centre - dQd;
	auto Qu = centre + dQd;

	std::vector<Pnt2d> Pts(4);
	Pts[0] = Qd + dQr;
	Pts[1] = Qu + dQr;
	Pts[2] = Qu - dQr;
	Pts[3] = Qd - dQr;

	auto box = Entity2d_Box::BoundingBoxOf(Pts);
	return std::move(box);
}

AutLib::SizeMap2d_FullIntAnIso::box
AutLib::SizeMap2d_FullIntAnIso::CalcEffectiveRegion
(
	const Standard_Real theRadius,
	const Point & theCentre,
	const frontType & /*theEdge*/
) const
{
	std::vector<Pnt2d> Pts(4);

	Pts[0] = theCentre - Pnt2d(0, theRadius);
	Pts[1] = theCentre + Pnt2d(theRadius, 0);
	Pts[2] = theCentre + Pnt2d(0, theRadius);
	Pts[3] = theCentre - Pnt2d(theRadius, 0);

	Pts[0] = CorrEffRegion(theCentre, Pts[0], theRadius);
	Pts[1] = CorrEffRegion(theCentre, Pts[1], theRadius);
	Pts[2] = CorrEffRegion(theCentre, Pts[2], theRadius);
	Pts[3] = CorrEffRegion(theCentre, Pts[3], theRadius);

	auto box = Entity2d_Box::BoundingBoxOf(Pts);
	return std::move(box);
}

AutLib::SizeMap2d_FullIntAnIso::metric
AutLib::SizeMap2d_FullIntAnIso::CalcEffectiveMetric
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
) const
{
	auto nbSegments = Info()->NbSamples();
	if (nbSegments IS_EQUAL 1)
	{
		auto m = MetricMap()->MetricAt(MEAN(theP0, theP1));
		auto dP = theP1 - theP0;

		auto d = CalcDistance(theP0, theP1);
		auto landa = d / DotProduct(dP, m.Multiplied(dP));

		m *= (landa*landa);
		return std::move(m);
	}

	auto du = 1.0 / (Standard_Real)nbSegments;
	auto dP = theP1 - theP0;
	auto dPu = dP * du;

	std::vector<Entity2d_Metric1> metrics;
	metrics.reserve(nbSegments);
	forThose(Index, 1, nbSegments)
	{
		auto P = dPu * Index + theP0 - 0.5*dPu;

		auto m = MetricMap()->MetricAt(P);
		metrics.push_back(std::move(m));
	}

	auto ms = metrics[0];
	forThose(Index, 1, metrics.size() - 1)
	{
		ms = Entity2d_Metric1::IntersectionSR(ms, metrics[Index]);
	}

	auto d = CalcDistance(theP0, theP1);
	auto landa = d / Entity2d_Metric1::Distance(theP0, theP1, ms);

	ms *= (landa*landa);
	return std::move(ms);
}

void AutLib::SizeMap2d_FullIntAnIso::Make()
{
	if (NOT SizeMap())
	{
		FatalErrorIn("void AutLib::SizeMap2d_FullIntAnIso::Make()") << endl
			<< "No size map has been specified!" << endl
			<< abort(FatalError);
	}

	if (NOT MetricMap())
	{
		FatalErrorIn("void AutLib::SizeMap2d_FullIntAnIso::Make()") << endl
			<< "no metric map has been specified!" << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}

std::shared_ptr<AutLib::Entity2d_Eigen>
AutLib::size_map2d_full_aniso_adapt_eigen = std::make_shared<AutLib::Entity2d_Eigen>();