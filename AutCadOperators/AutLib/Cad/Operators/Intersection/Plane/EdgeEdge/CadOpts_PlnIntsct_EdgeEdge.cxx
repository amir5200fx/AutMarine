#include <CadOpts_PlnIntsct_EdgeEdge.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Cad_Tools.hxx>
#include <CadOpts_PlnIntsct_Info.hxx>
#include <CadOpts_PlnIntsct_Data.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_InterCurveCurve.hxx>

void AutLib::CadOpts_PlnIntsct_EdgeEdge::Perform()
{
	if (NOT Edge0())
	{
		FatalErrorIn("void Perform()")
			<< "the edge0 has not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Edge1())
	{
		FatalErrorIn("void Perform()")
			<< "the edge1 has not been loaded!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Edge0()->Curve());
	Debug_Null_Pointer(Edge1()->Curve());

	const auto& curve0 = *Edge0()->Curve();
	const auto& curve1 = *Edge1()->Curve();

	auto Inter =
		Cad_Tools::Intersection(curve0.Curve(), curve1.Curve(), Info()->Tolerance());

	const auto& alg = Inter->Intersector();

	auto data = std::make_shared<CadOpts_PlnIntsctEdgeEdge_Data>(Edge0(), Edge1());
	Debug_Null_Pointer(data);

	auto& pts = data->Points();
	forThose(Index, 1, alg.NbPoints())
	{
		const auto& pt = alg.Point(Index);

		auto IntPts = std::make_shared<CadOpts_PlnIntsctData_Point>();
		Debug_Null_Pointer(IntPts);

		IntPts->SetParameter1(pt.ParamOnFirst());
		IntPts->SetParameter2(pt.ParamOnSecond());

		IntPts->SetCoord(pt.Value());

		pts.push_back(std::move(IntPts));
	}

	auto& segments = data->Segments();
	forThose(Index, 1, alg.NbSegments())
	{
		const auto& seg = alg.Segment(Index);

		auto IntSeg = std::make_shared<CadOpts_PlnIntsctData_Segment>();
		Debug_Null_Pointer(IntSeg);

		if (NOT seg.HasFirstPoint())
		{
			FatalErrorIn("void AutLib::CadOpts_PlnIntsct_EdgeEdge::Perform()")
				<< "Invalid Data: the segment has no first point"
				<< abort(FatalError);
		}

		if (NOT seg.HasLastPoint())
		{
			FatalErrorIn("void AutLib::CadOpts_PlnIntsct_EdgeEdge::Perform()")
				<< "Invalid Data: the segment has no last point"
				<< abort(FatalError);
		}

		const auto& pt1 = seg.FirstPoint();
		const auto& pt2 = seg.LastPoint();

		IntSeg->SetOpposite(seg.IsOpposite());

		auto IntPts1 = std::make_shared<CadOpts_PlnIntsctData_Point>();
		Debug_Null_Pointer(IntPts1);

		IntPts1->SetParameter1(pt1.ParamOnFirst());
		IntPts1->SetParameter2(pt1.ParamOnSecond());

		IntPts1->SetCoord(pt1.Value());

		auto IntPts2 = std::make_shared<CadOpts_PlnIntsctData_Point>();
		Debug_Null_Pointer(IntPts2);

		IntPts2->SetParameter1(pt2.ParamOnFirst());
		IntPts2->SetParameter2(pt2.ParamOnSecond());

		IntPts2->SetCoord(pt2.Value());

		IntSeg->SetEnt1(std::move(IntPts1));
		IntSeg->SetEnt2(std::move(IntPts2));

		segments.push_back(std::move(IntSeg));
	}

	theData_ = std::move(data);

	Change_IsDone() = Standard_True;
}