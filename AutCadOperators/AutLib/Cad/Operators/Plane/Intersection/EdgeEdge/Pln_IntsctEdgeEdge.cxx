#include <Pln_IntsctEdgeEdge.hxx>

#include <Global_Macros.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_IntsctPoint.hxx>
#include <Pln_IntscSegment.hxx>
#include <Pln_IntsctPair.hxx>
#include <Cad_Tools.hxx>
#include <Pln_IntsctEdgeEdgeInfo.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Standard_Handle.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dInt_GInter.hxx>
#include <Geom2d_Curve.hxx>

const std::shared_ptr<AutLib::Pln_IntsctPair>& 
AutLib::Pln_IntsctEdgeEdge::Entity
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, NbEntities() - 1))
	{
		FatalErrorIn("const std::shared_ptr<Pln_IntsctPair>& Entity(const Standard_Integer theIndex) const")
			<< "Invalid index : " << theIndex << endl
			<< " - nb. of entities: " << NbEntities() << endl
			<< abort(FatalError);
	}
	return theEntities_[theIndex];
}

void AutLib::Pln_IntsctEdgeEdge::Perform()
{
	if (NOT Edge0())
	{
		FatalErrorIn("void Perform()")
			<< "Null edge0" << endl
			<< abort(FatalError);
	}

	if (NOT Edge1())
	{
		FatalErrorIn("void Perform()")
			<< "Null edge1" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Edge0()->Curve());
	Debug_Null_Pointer(Edge1()->Curve());

	const auto& curve0 = *Edge0()->Curve();
	const auto& curve1 = *Edge1()->Curve();

	auto Inter = 
		Cad_Tools::Intersection(curve0.Curve(), curve1.Curve(), Info()->Tolerance());

	const auto& alg = Inter->Intersector();

	auto& entities = ChangeEntities();
	entities.reserve(alg.NbPoints() + alg.NbPoints());

	forThose(Index, 1, alg.NbPoints())
	{
		const auto& pt = alg.Point(Index);
		
		auto pair = std::make_shared<Pln_IntsctPair>();
		Debug_Null_Pointer(pair);

		auto entity0 = std::make_shared<Pln_IntsctPoint>();
		auto entity1 = std::make_shared<Pln_IntsctPoint>();
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetEdge(Edge0());
		entity1->SetEdge(Edge1());

		entity0->SetCoord(pt.Value());
		entity1->SetCoord(pt.Value());

		entity0->SetParameter(pt.ParamOnFirst());
		entity1->SetParameter(pt.ParamOnSecond());

		pair->SetEntity0(entity0);
		pair->SetEntity1(entity1);

		entities.push_back(pair);
	}

	forThose(Index, 1, alg.NbSegments())
	{
		const auto& seg = alg.Segment(Index);
		
		auto pair = std::make_shared<Pln_IntsctPair>();
		Debug_Null_Pointer(pair);

		auto entity0 = std::make_shared<Pln_IntsctSegment>();
		auto entity1 = std::make_shared<Pln_IntsctSegment>();
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetEdge(Edge0());
		entity1->SetEdge(Edge1());

		entity0->SetFirstPointCondition(seg.HasFirstPoint());
		entity1->SetLastPointCondition(seg.HasLastPoint());

		const auto& pt0 = seg.FirstPoint();
		const auto& pt1 = seg.LastPoint();

		if (seg.HasFirstPoint())
		{
			entity0->SetCoord0(pt0.Value());
			entity1->SetCoord0(pt0.Value());

			entity0->SetParameter0(pt0.ParamOnFirst());
			entity1->SetParameter0(pt0.ParamOnSecond());
		}

		if (seg.HasLastPoint())
		{
			entity0->SetCoord1(pt1.Value());
			entity1->SetCoord1(pt1.Value());

			entity0->SetParameter1(pt1.ParamOnFirst());
			entity1->SetParameter1(pt1.ParamOnSecond());
		}

		if (seg.HasFirstPoint() AND seg.HasLastPoint())
		{
			if (pt0.ParamOnFirst() >= pt1.ParamOnFirst())
			{
				FatalErrorIn("void Perform()")
					<< "Invalid segment: " << endl
					<< " - first parameter: " << pt0.ParamOnFirst() << endl
					<< " - last parameter: " << pt1.ParamOnFirst() << endl
					<< abort(FatalError);
			}

			if (pt0.ParamOnSecond() >= pt1.ParamOnSecond())
			{
				FatalErrorIn("void Perform()")
					<< "Invalid segment: " << endl
					<< " - first parameter: " << pt0.ParamOnSecond() << endl
					<< " - last parameter: " << pt1.ParamOnSecond() << endl
					<< abort(FatalError);
			}

			auto segCurve0 = Cad_Tools::ConvertToTrimmedCurve(curve0.Curve(), pt0.ParamOnFirst(), pt1.ParamOnFirst());
			auto segCurve1 = Cad_Tools::ConvertToTrimmedCurve(curve1.Curve(), pt0.ParamOnSecond(), pt1.ParamOnSecond());

			entity0->SetSegment(segCurve0);
			entity1->SetSegment(segCurve1);
		}

		pair->SetEntity0(entity0);
		pair->SetEntity1(entity1);

		entities.push_back(pair);
	}
}