#include <Aft2d_SegmentEdge.hxx>

#include <Entity2d_Chain.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_PoleNodeTemplate.hxx>
#include <Aft2d_PoleEdgeTemplate.hxx>
#include <Aft2d_LineNodeTemplate.hxx>
#include <Aft2d_LineEdgeTemplate.hxx>
#include <Aft2d_Node.hxx>
#include <Aft2d_CornerNode.hxx>
#include <Aft2d_SegmentNode.hxx>

#include <error.hxx>
#include <OSstream.hxx>

template<>
std::vector<std::shared_ptr<AutLib::Aft2d_SegmentEdge>>
AutLib::Aft2d_SegmentEdge::GetTopology
(
	const Entity2d_Chain& theChain,
	const std::shared_ptr<typename Aft2d_TBndEdgeTraits::curveType>& theCurve
)
{
	const auto& pts = theChain.Points();
	if (pts.size() < 2)
	{
		FatalErrorIn("std::vector<std::shared_ptr<AutLib::Aft2d_SegmentEdge>> AutLib::Aft2d_SegmentEdge::GetTopology()")
			<< "Invalid chain: a valid chain must have more than 2 points" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Aft2d_Node>> nodes;
	nodes.reserve(pts.size());

	Standard_Integer K = 0;
	auto n0 = std::make_shared<Aft2d_CornerNode>(++K, pts[K - 1]);
	nodes.push_back(n0);
	n0->InsertToCurves(theCurve->Index(), theCurve);

	forThose(Index, 1, pts.size() - 2)
	{
		auto n = std::make_shared<Aft2d_SegmentNode>(++K, pts[K - 1]);
		nodes.push_back(n);

		n->SetCurve(theCurve);
	}

	auto n1 = std::make_shared<Aft2d_CornerNode>(++K, pts[K - 1]);
	nodes.push_back(n1);
	n1->InsertToCurves(theCurve->Index(), theCurve);

	const auto& connect = theChain.Connectivity();

	std::vector<std::shared_ptr<Aft2d_SegmentEdge>> edges;
	edges.reserve(connect.size());

	K = 0;
	for (const auto& x : connect)
	{
		const auto& n0 = nodes[Index_Of(x.Value(0))];
		const auto& n1 = nodes[Index_Of(x.Value(1))];

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto edge = std::make_shared<Aft2d_SegmentEdge>(++K, n0, n1);
		Debug_Null_Pointer(edge);

		edges.push_back(edge);

		edge->SetCurve(theCurve);
	}
	return std::move(edges);
}

template<>
void AutLib::Aft2d_SegmentEdge::MergeDangles
(
	const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theWire,
	const Standard_Real theTol
)
{
	forThose(Index, 1, theWire.size() - 1)
	{
		Debug_Null_Pointer(theWire[Index - 1]);
		Debug_Null_Pointer(theWire[Index]);

		auto& e0 = *theWire[Index - 1];
		auto& e1 = *theWire[Index];

		if (e0.Node1() IS_EQUAL e1.Node0())
			continue;

		if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Invalid Wire" << endl
				<< abort(FatalError);
		}

		const auto sn0 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e0.Node1());
		const auto sn1 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e1.Node0());

		if (sn0 AND sn1)
		{
			auto node =
				Aft2d_SegmentNode::MergeNodes(sn0, sn1, Aft2d_SegmentNode::Merge_Alg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);

			continue;
		}

		const auto cn0 = std::dynamic_pointer_cast<Aft2d_CornerNode>(e0.Node1());
		const auto cn1 = std::dynamic_pointer_cast<Aft2d_CornerNode>(e1.Node0());

		if (sn0 AND sn1)
		{
			auto node =
				Aft2d_CornerNode::MergeNodes(cn0, cn1, Aft2d_CornerNode::Merge_Alg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);

			continue;
		}

		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}

	auto& e0 = *theWire[theWire.size() - 1];
	auto& e1 = *theWire[0];

	if (e0.Node1() IS_EQUAL e1.Node0())
		return;

	if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}

	const auto sn0 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e0.Node1());
	const auto sn1 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e1.Node0());

	if (sn0 AND sn1)
	{
		auto node =
			Aft2d_SegmentNode::MergeNodes(sn0, sn1, Aft2d_SegmentNode::Merge_Alg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);

		return;
	}

	const auto cn0 = std::dynamic_pointer_cast<Aft2d_CornerNode>(e0.Node1());
	const auto cn1 = std::dynamic_pointer_cast<Aft2d_CornerNode>(e1.Node0());

	if (sn0 AND sn1)
	{
		auto node =
			Aft2d_CornerNode::MergeNodes(cn0, cn1, Aft2d_CornerNode::Merge_Alg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);

		return;
	}

	FatalErrorIn(FunctionSIG) << endl
		<< "Invalid Wire" << endl
		<< abort(FatalError);
}