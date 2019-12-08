#include <Aft2d_SegmentEdgeAnIso.hxx>

#include <Entity2d_Chain.hxx>
#include <Mesh2d_PlnCurveAnIso.hxx>
#include <Aft2d_PoleNodeTemplate.hxx>
#include <Aft2d_PoleEdgeTemplate.hxx>
#include <Aft2d_LineNodeTemplate.hxx>
#include <Aft2d_LineEdgeTemplate.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <Aft2d_CornerNodeAnIso.hxx>
#include <Aft2d_SegmentNodeAnIso.hxx>

#include <error.hxx>
#include <OSstream.hxx>

template<>
std::vector<std::shared_ptr<AutLib::Aft2d_SegmentEdgeAnIso>>
AutLib::Aft2d_SegmentEdgeAnIso::GetTopology
(
	const Entity2d_Chain& theChain,
	const std::shared_ptr<typename Aft2d_TBndEdgeAnIsoTraits::curveType>& theCurve
)
{
	const auto& pts = theChain.Points();
	if (pts.size() < 2)
	{
		FatalErrorIn("std::vector<std::shared_ptr<AutLib::Aft2d_SegmentEdgeAnIso>> AutLib::Aft2d_SegmentEdgeAnIso::GetTopology()")
			<< "Invalid chain: a valid chain must have more than 2 points" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Aft2d_NodeAnIso>> nodes;
	nodes.reserve(pts.size());

	Standard_Integer K = 0;
	auto n0 = std::make_shared<Aft2d_CornerNodeAnIso>(++K, pts[K - 1]);
	nodes.push_back(n0);
	n0->InsertToCurves(theCurve->Index(), theCurve);

	forThose(Index, 1, pts.size() - 2)
	{
		auto n = std::make_shared<Aft2d_SegmentNodeAnIso>(++K, pts[K - 1]);
		nodes.push_back(n);

		n->SetCurve(theCurve);
	}

	auto n1 = std::make_shared<Aft2d_CornerNodeAnIso>(++K, pts[K - 1]);
	nodes.push_back(n1);
	n1->InsertToCurves(theCurve->Index(), theCurve);

	const auto& connect = theChain.Connectivity();

	std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>> edges;
	edges.reserve(connect.size());

	K = 0;
	for (const auto& x : connect)
	{
		const auto& n0 = nodes[Index_Of(x.Value(0))];
		const auto& n1 = nodes[Index_Of(x.Value(1))];

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto edge = std::make_shared<Aft2d_SegmentEdgeAnIso>(++K, n0, n1);
		Debug_Null_Pointer(edge);

		edges.push_back(edge);

		edge->SetCurve(theCurve);
	}
	return std::move(edges);
}