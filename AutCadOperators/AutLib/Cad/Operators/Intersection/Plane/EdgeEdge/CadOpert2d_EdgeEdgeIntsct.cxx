#include <CadOpert2d_EdgeEdgeIntsct.hxx>

#include <Global_Macros.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Cad_Tools.hxx>
#include <CadOpert2d_IntsctPair.hxx>
#include <CadOpert2d_IntsctPoint.hxx>
#include <CadOpert2d_IntsctSegment.hxx>
#include <CadOpert2d_EdgeEdgeIntsct_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Standard_Handle.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dInt_GInter.hxx>
#include <Geom2d_Curve.hxx>

const std::shared_ptr<AutLib::CadOpert2d_IntsctPair>& 
AutLib::CadOpert2d_EdgeEdgeIntsct::Entity
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, NbEntities() - 1))
	{
		FatalErrorIn("const std::shared_ptr<CadOpert2d_IntsctPair>& Entity(const Standard_Integer theIndex) const")
			<< "Invalid index : " << theIndex << endl
			<< " - nb. of entities: " << NbEntities() << endl
			<< abort(FatalError);
	}
	return theEntities_[theIndex];
}

void AutLib::CadOpert2d_EdgeEdgeIntsct::Perform()
{
	if (NOT Edge0())
	{
		FatalErrorIn("void Perform()")
			<< "Edge0 has not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Edge1())
	{
		FatalErrorIn("void Perform()")
			<< "Edge1 has not been loaded!" << endl
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

		auto pair = std::make_shared<CadOpert2d_IntsctPair>();
		Debug_Null_Pointer(pair);

		auto entity0 = std::make_shared<CadOpert2d_IntsctPoint>();
		auto entity1 = std::make_shared<CadOpert2d_IntsctPoint>();
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

		if (NOT seg.HasFirstPoint())
		{
			FatalErrorIn("void Perform()") << endl
				<< "the segment deos not have first point!" << endl
				<< abort(FatalError);
		}

		if (NOT seg.HasLastPoint())
		{
			FatalErrorIn("void Perform()") << endl
				<< "the segment deos not have first point!" << endl
				<< abort(FatalError);
		}

		auto pair = std::make_shared<CadOpert2d_IntsctPair>();
		Debug_Null_Pointer(pair);

		auto entity0 = std::make_shared<CadOpert2d_IntsctSegment>();
		auto entity1 = std::make_shared<CadOpert2d_IntsctSegment>();
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetEdge(Edge0());
		entity1->SetEdge(Edge1());

		const auto& pt0 = seg.FirstPoint();
		const auto& pt1 = seg.LastPoint();

		entity0->SetCoord0(pt0.Value());
		entity0->SetCoord1(pt1.Value());
		entity0->SetParameter0(pt0.ParamOnFirst());
		entity0->SetParameter1(pt1.ParamOnFirst());

		if (seg.IsOpposite())
		{
			entity1->SetCoord0(pt1.Value());
			entity1->SetCoord1(pt0.Value());
			entity1->SetParameter0(pt1.ParamOnSecond());
			entity1->SetParameter1(pt0.ParamOnSecond());
		}
		else
		{
			entity1->SetCoord0(pt0.Value());
			entity1->SetCoord1(pt1.Value());
			entity1->SetParameter0(pt0.ParamOnSecond());
			entity1->SetParameter1(pt1.ParamOnSecond());
		}

		pair->SetEntity0(entity0);
		pair->SetEntity1(entity1);

		entities.push_back(pair);
	}

	Change_IsDone() = Standard_True;
}