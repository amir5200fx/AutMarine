#include <CadOpts_PlnIntsct_EdgeEdge.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Cad_Tools.hxx>
#include <CadOpts_PlnIntsct_Info.hxx>
#include <CadOpts_PlnIntsct_Data.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_InterCurveCurve.hxx>

//void AutLib::CadOpts_PlnIntsct_EdgeEdge::Perform()
//{
//	if (NOT Edge0())
//	{
//		FatalErrorIn("void Perform()")
//			<< "the edge0 has not been loaded!" << endl
//			<< abort(FatalError);
//	}
//
//	if (NOT Edge1())
//	{
//		FatalErrorIn("void Perform()")
//			<< "the edge1 has not been loaded!" << endl
//			<< abort(FatalError);
//	}
//
//	Debug_Null_Pointer(Edge0()->Curve());
//	Debug_Null_Pointer(Edge1()->Curve());
//
//	const auto& curve0 = *Edge0()->Curve();
//	const auto& curve1 = *Edge1()->Curve();
//
//	auto Inter =
//		Cad_Tools::Intersection(curve0.Curve(), curve1.Curve(), Info()->Tolerance());
//
//	const auto& alg = Inter->Intersector();
//
//	forThose(Index, 1, alg.NbPoints())
//	{
//		const auto& pt = alg.Point(Index);
//
//		
//	}
//}