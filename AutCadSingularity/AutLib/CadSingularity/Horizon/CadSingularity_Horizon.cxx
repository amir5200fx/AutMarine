#include <CadSingularity_Horizon.hxx>

#include <Entity2d_Chain.hxx>
#include <GeoMesh2d_MetricBackground.hxx>
#include <CadRepair_ApproxSurfMetric.hxx>
#include <CadRepair_ApproxSurfMetric_Info.hxx>
#include <Entity2d_Polygon.hxx>
#include <Mesh2d_KnitChain.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean AutLib::CadSingularity_Horizon::IsLoaded() const
{
	return (Standard_Boolean)theMetric_;
}

Standard_Boolean AutLib::CadSingularity_Horizon::HasHorizon() const
{
	if (NOT IsDone())
	{
		FatalErrorIn("Standard_Boolean AutLib::CadSingularity_Horizon::HasHorizon() const")
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	if (NOT Chain()) return Standard_False;
	return (Standard_Boolean)Chain()->NbPolygons();
}

Standard_Integer AutLib::CadSingularity_Horizon::NbHorizons() const
{
	if (NOT IsDone())
	{
		FatalErrorIn("Standard_Integer AutLib::CadSingularity_Horizon::NbHorizons() const")
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	if (NOT Chain())
	{
		FatalErrorIn("Standard_Integer AutLib::CadSingularity_Horizon::NbHorizons() const")
			<< "no horizon has been found!" << endl
			<< abort(FatalError);
	}
	return Chain()->NbPolygons();
}

const std::shared_ptr<AutLib::Entity2d_Polygon>
AutLib::CadSingularity_Horizon::Horizon
(
	const Standard_Integer theIndex
) const
{
	if (NOT IsDone())
	{
		FatalErrorIn("const std::shared_ptr<Entity2d_Polygon> Horizon(const Standard_Integer theIndex) const")
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	if (NOT Chain())
	{
		FatalErrorIn("const std::shared_ptr<Entity2d_Polygon> Horizon(const Standard_Integer theIndex) const")
			<< "no horizon has been found!" << endl
			<< abort(FatalError);
	}
	return Chain()->Polygon(theIndex);
}

#include <Entity_Segment.hxx>
#include <Entity_Triangle.hxx>

#include <Geom_Surface.hxx>

namespace AutLib
{
	typedef Entity2d_Metric1 metric;

	typedef Entity_Segment<const Pnt2d&> segmentRef;
	typedef Entity_Triangle<const Pnt2d&> triangle;
	typedef Entity_Segment<Pnt2d> segment;

	template<class SizeMap = void>
	struct MetricAt
	{
		static metric _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const Pnt2d& theP
		)
		{
			auto u = theP.X();
			auto v = theP.Y();

			gp_Vec D1U, D1V;
			gp_Pnt P;
			theSurface.D1(u, v, P, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			const auto h = theMap.Value(theP);
			Debug_If_Condition(h <= gp::Resolution());

			const auto invH = 1.0 / (h*h);

			metric M(invH*A, invH*B, invH*C);
			return std::move(M);
		}
	};

	template<>
	struct MetricAt<void>
	{
		static metric _
		(
			const Geom_Surface& theSurface,
			const Pnt2d& theP
		)
		{
			auto u = theP.X();
			auto v = theP.Y();

			gp_Vec D1U, D1V;
			gp_Pnt P;
			theSurface.D1(u, v, P, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			metric M(A, B, C);
			return std::move(M);
		}
	};

	template<class SizeMap = void>
	struct Interpolate
	{

		static Standard_Boolean _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const segmentRef& s,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Pnt2d& theCoord
		)
		{
			const auto& P0 = s.P0();
			const auto& P1 = s.P1();

			auto m0 = MetricAt<SizeMap>::_(theSurface, theMap, P0);
			auto m1 = MetricAt<SizeMap>::_(theSurface, theMap, P1);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;

			if (det0 > theDegeneracy AND det1 > theDegeneracy)
				return Standard_False;

			if (det0 <= theDegeneracy AND det1 <= theDegeneracy)
				return Standard_False;

			auto t = (theDegeneracy - det0) / (det1 - det0);
			if (t < 0) return Standard_False;
			if (t > 1) return Standard_False;

			theCoord = P0 + t * (P1 - P0);
			return Standard_True;
		}
	};

	template<>
	struct Interpolate<void>
	{

		static Standard_Boolean _
		(
			const Geom_Surface& theSurface,
			const segmentRef& s,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Pnt2d& theCoord
		)
		{
			const auto& P0 = s.P0();
			const auto& P1 = s.P1();

			auto m0 = MetricAt<void>::_(theSurface, P0);
			auto m1 = MetricAt<void>::_(theSurface, P1);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;

			if (det0 > theDegeneracy AND det1 > theDegeneracy)
				return Standard_False;

			if (det0 <= theDegeneracy AND det1 <= theDegeneracy)
				return Standard_False;

			auto t = (theDegeneracy - det0) / (det1 - det0);
			if (t < 0) return Standard_False;
			if (t > 1) return Standard_False;

			theCoord = P0 + t * (P1 - P0);
			return Standard_True;
		}
	};

	static void MergingThreePoints
	(
		const Pnt2d& P0,
		const Pnt2d& P1,
		const Pnt2d& P2,
		const Standard_Real theTol,
		Pnt2d& Q0,
		Pnt2d& Q1
	)
	{
		auto tol2 = theTol * theTol;
		if (P0.SquareDistance(P1) > tol2)
		{
			Q0 = P0;
			Q1 = P1;
			return;
		}

		if (P0.SquareDistance(P2) > tol2)
		{
			Q0 = P0;
			Q1 = P2;
			return;
		}

		if (P1.SquareDistance(P2) > tol2)
		{
			Q0 = P1;
			Q1 = P2;
			return;
		}
	}

	static Standard_Integer StandPoint
	(
		const Standard_Real det0,
		const Standard_Real det1,
		const Standard_Real det2,
		const Standard_Real theDegeneracy
	)
	{
		if (det0 <= theDegeneracy AND det1 <= theDegeneracy AND det2 <= theDegeneracy)
		{
			FatalErrorIn("Pnt2d StandPoint(const triangle& theTriangle, const Standard_Real det0, const Standard_Real det1, const Standard_Real det2, const Standard_Real theDegeneracy)")
				<< "Invalid Data : " << endl
				<< " - All of the determinants of the triangle are less than the degeneracy criterion!" << endl
				<< " - d0 = " << det0 << ", d1 = " << det1 << ", d2 = " << det2 << endl
				<< " - Degeneracy criterion = " << theDegeneracy << endl
				<< abort(FatalError);
		}

		Standard_Integer gt_deg, st_deg;
		gt_deg = 0;
		st_deg = 0;
		det0 <= theDegeneracy ? st_deg++ : gt_deg++;
		det1 <= theDegeneracy ? st_deg++ : gt_deg++;
		det2 <= theDegeneracy ? st_deg++ : gt_deg++;

		if (st_deg IS_EQUAL 1)
		{
			if (det0 <= theDegeneracy) return 0;
			if (det1 <= theDegeneracy) return 1;
			if (det2 <= theDegeneracy) return 2;
		}

		if (gt_deg IS_EQUAL 1)
		{
			if (det0 > theDegeneracy) return 0;
			if (det1 > theDegeneracy) return 1;
			if (det2 > theDegeneracy) return 2;
		}

		FatalErrorIn("Pnt2d StandPoint(const triangle& theTriangle, const Standard_Real det0, const Standard_Real det1, const Standard_Real det2, const Standard_Real theDegeneracy)")
			<< "Invalid Data : " << endl
			<< " - something goes wrong!" << endl
			<< abort(FatalError);

		return 0;
	}

	template<class SizeMap = void>
	struct CheckOrientation
	{

		static void _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Entity2d_Chain& theSeg
		)
		{
			const auto& P0 = theTriangle.P0();
			const auto& P1 = theTriangle.P1();
			const auto& P2 = theTriangle.P2();

			auto m0 = MetricAt<SizeMap>::_(theSurface, theMap, P0);
			auto m1 = MetricAt<SizeMap>::_(theSurface, theMap, P1);
			auto m2 = MetricAt<SizeMap>::_(theSurface, theMap, P2);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;
			auto det2 = m2.Determinant() * theInvMaxDet;

			const auto& P = theTriangle.Vertex(StandPoint(det0, det1, det2, theDegeneracy));

			auto& pts = theSeg.Points();
			const auto& V0 = pts[0];
			const auto& V1 = pts[1];

			if (CrossProduct(V0 - P, V1 - P) < 0)
			{
				std::reverse(pts.begin(), pts.end());
			}
		}
	};

	template<>
	struct CheckOrientation<void>
	{

		static void _
		(
			const Geom_Surface& theSurface,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Entity2d_Chain& theSeg
		)
		{
			const auto& P0 = theTriangle.P0();
			const auto& P1 = theTriangle.P1();
			const auto& P2 = theTriangle.P2();

			auto m0 = MetricAt<void>::_(theSurface, P0);
			auto m1 = MetricAt<void>::_(theSurface, P1);
			auto m2 = MetricAt<void>::_(theSurface, P2);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;
			auto det2 = m2.Determinant() * theInvMaxDet;

			const auto& P = theTriangle.Vertex(StandPoint(det0, det1, det2, theDegeneracy));

			auto& pts = theSeg.Points();
			const auto& V0 = pts[0];
			const auto& V1 = pts[1];

			if (CrossProduct(V0 - P, V1 - P) < 0)
			{
				std::reverse(pts.begin(), pts.end());
			}
		}
	};

	template<class SizeMap = void>
	struct GetPathFromTriangle
	{

		static std::shared_ptr<Entity2d_Chain> _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theMergTol,
			const Standard_Real theInvMaxDet
		)
		{
			auto seg =
				std::make_shared<Entity2d_Chain>();

			std::vector<Pnt2d> Pts;
			Pts.reserve(3);

			Pnt2d Coord;
			if (Interpolate<SizeMap>::_(theSurface, theMap, theTriangle.Segment(0), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<SizeMap>::_(theSurface, theMap, theTriangle.Segment(1), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<SizeMap>::_(theSurface, theMap, theTriangle.Segment(2), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Pts.empty())
			{
				return nullptr;
			}

			Pnt2d Q0, Q1;
			if (Pts.size() > 2)
			{
				MergingThreePoints(Pts[0], Pts[1], Pts[2], theMergTol, Q0, Q1);
			}
			else
			{
				Q0 = Pts[0];
				Q1 = Pts[1];
			}

			auto& points = seg->Points();
			points.resize(2);

			points[0] = Q0;
			points[1] = Q1;

			auto& Indices = seg->Connectivity();
			Indices.resize(1);
			Indices[0].Value(0) = 1;
			Indices[0].Value(1) = 2;

			CheckOrientation<SizeMap>::_(theSurface, theMap, theTriangle, theDegeneracy, theInvMaxDet, *seg);

			return std::move(seg);
		}
	};

	template<>
	struct GetPathFromTriangle<void>
	{

		static std::shared_ptr<Entity2d_Chain> _
		(
			const Geom_Surface& theSurface,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theMergTol,
			const Standard_Real theInvMaxDet
		)
		{
			auto seg =
				std::make_shared<Entity2d_Chain>();

			std::vector<Pnt2d> Pts;
			Pts.reserve(3);

			Pnt2d Coord;
			if (Interpolate<void>::_(theSurface, theTriangle.Segment(0), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<void>::_(theSurface, theTriangle.Segment(1), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<void>::_(theSurface, theTriangle.Segment(2), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Pts.empty())
			{
				return nullptr;
			}

			Pnt2d Q0, Q1;
			if (Pts.size() > 2)
			{
				MergingThreePoints(Pts[0], Pts[1], Pts[2], theMergTol, Q0, Q1);
			}
			else
			{
				Q0 = Pts[0];
				Q1 = Pts[1];
			}

			auto& points = seg->Points();
			points.resize(2);

			points[0] = Q0;
			points[1] = Q1;

			auto& Indices = seg->Connectivity();
			Indices.resize(1);
			Indices[0].Value(0) = 1;
			Indices[0].Value(1) = 2;

			CheckOrientation<void>::_(theSurface, theTriangle, theDegeneracy, theInvMaxDet, *seg);

			return std::move(seg);
		}
	};
}

#include <Geo2d_SizeFunction.hxx>
#include <Merge_StaticData.hxx>

void AutLib::CadSingularity_Horizon::Perform()
{
	if (NOT IsLoaded())
	{
		FatalErrorIn("void AutLib::CadSingularity_Horizon::Perform()")
			<< "Not metric has been loaded!"
			<< abort(FatalError);
	}

	if (NOT Metric()->Approx())
	{
		FatalErrorIn("void AutLib::CadSingularity_Horizon::Perform()")
			<< "no surface metric approximation has been found!"
			<< abort(FatalError);
	}

	if (NOT Metric()->Surface())
	{
		FatalErrorIn("void AutLib::CadSingularity_Horizon::Perform()")
			<< "no surface has been found!"
			<< abort(FatalError);
	}

	const auto& apprx = *Metric()->Approx();

	Debug_Null_Pointer(apprx.Mesh());
	const auto& mesh = *apprx.Mesh();
	const auto& sources = apprx.Sources();

	Debug_Null_Pointer(Metric()->Info());
	const auto& info = *Metric()->Info();

	const auto& surface = *Metric()->Surface();

	const auto invMaxDet = (Standard_Real)1.0 / Metric()->MaxDet();

	std::vector<std::shared_ptr<Entity2d_Chain>> list;

	const auto& elements = mesh.Elements();
	if (Metric()->SizeFunction())
	{
		for (const auto& x : elements)
		{
			Debug_Null_Pointer(x);
			const auto& element = *x;

			const auto& p0 = element.Node0()->Coord();
			const auto& p1 = element.Node1()->Coord();
			const auto& p2 = element.Node2()->Coord();

			triangle t(p0, p1, p2);

			auto path =
				GetPathFromTriangle<Geo2d_SizeFunction>::_
				(
					surface,
					*Metric()->SizeFunction(),
					t,
					info.Degeneracy(),
					info.Tolerance(), invMaxDet);

			if (path) list.push_back(path);
		}
	}
	else
	{
		for (const auto& x : elements)
		{
			Debug_Null_Pointer(x);
			const auto& element = *x;

			const auto& p0 = element.Node0()->Coord();
			const auto& p1 = element.Node1()->Coord();
			const auto& p2 = element.Node2()->Coord();

			triangle t(p0, p1, p2);

			auto path =
				GetPathFromTriangle<>::_
				(
					surface,
					t,
					info.Degeneracy(),
					info.Tolerance(), invMaxDet);

			if (path) list.push_back(path);
		}
	}

	if (list.empty())
	{
		Change_IsDone() = Standard_True;
		return;
	}

	Merge_StaticData<Entity2d_Chain> merge;
	merge.Import(list);
	merge.SetRemoveDegeneracy();

	merge.Perform();

	const auto& merged = merge.Merged();
	Debug_Null_Pointer(merged);

	auto chain = std::make_shared<Mesh2d_KnitChain>();
	Debug_Null_Pointer(chain);

	chain->Import(*merged);

	chain->Perform();

	ChangeChain() = std::move(chain);

	Change_IsDone() = Standard_True;
}