#include <Cad3d_GModel.hxx>

#include <GModel_Edge.hxx>
#include <GModel_Curve.hxx>
#include <GModel_parCurve.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Surface.hxx>
#include <GModel_System.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <TopExp_Explorer.hxx>
#include <ShapeFix_Wire.hxx>
#include <BRepTools_WireExplorer.hxx>

namespace AutLib
{

	namespace gModel
	{

		static std::shared_ptr<GModel_Edge> GetNewEdge
		(
			Standard_Integer& K,
			const TopoDS_Edge edge,
			const TopoDS_Face theFace
		)
		{
			Standard_Real u0, u1, U0, U1;
			TopLoc_Location pLoc, eLoc;
			auto patch = BRep_Tool::Surface(theFace, pLoc);

			auto pCurve = BRep_Tool::CurveOnSurface(edge, patch, pLoc, u0, u1);
			auto Curve = BRep_Tool::Curve(edge, eLoc, U0, U1);

			if (NOT BRep_Tool::SameRange(edge))
			{
				BRepLib::SameRange(edge);
			}

			if (NOT BRep_Tool::SameParameter(edge))
			{
				FatalErrorIn(FunctionSIG)
					<< "It's supposed that the edge has SameParameter flag" << endl
					<< abort(FatalError);
			}

			if (NOT BRep_Tool::SameRange(edge))
			{
				FatalErrorIn(FunctionSIG)
					<< "It's supposed that the edge has SameRange flag" << endl
					<< abort(FatalError);
			}

			if (edge.Orientation() IS_EQUAL TopAbs_REVERSED)
			{
				auto temp = u1;
				u1 = pCurve->ReversedParameter(u0);
				u0 = pCurve->ReversedParameter(temp);
				pCurve->Reverse();
			}

			auto curveOnPlane = std::make_shared<GModel_parCurve>(u0, u1, pCurve, gModelSys::par_curve_info);

			std::shared_ptr<GModel_Edge> newEdge;

			++K;

			if (Curve)
			{
				auto curveOnSurface = std::make_shared<GModel_Curve>(U0, U1, Curve, gModelSys::curve_info);
				newEdge = std::make_shared<GModel_Edge>(K, curveOnPlane, curveOnSurface);
			}
			else
			{
				newEdge = std::make_shared<GModel_Edge>(K, curveOnPlane, nullptr);
			}
			return std::move(newEdge);
		}
	}
}