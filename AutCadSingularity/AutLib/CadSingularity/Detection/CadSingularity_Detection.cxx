#include <CadSingularity_Detection.hxx>

#include <Cad2d_Plane_System.hxx>
#include <CadPlnModel_Segment.hxx>

#include <Geom_Surface.hxx>

//std::vector<std::shared_ptr<AutLib::Pln_Curve>> 
//AutLib::singularityTools::RetrieveSides(const Entity2d_Box & theBox)
//{
//	CadPlnModel_Segment LineSegMaker;
//
//	std::vector<std::shared_ptr<Pln_Curve>> curves(4);
//	curves[0] = LineSegMaker(theBox.P0(), theBox.Corner(Box2d_PickAlgorithm_SE), sysLib::gl_pln_curve_info);
//	curves[1] = LineSegMaker(theBox.Corner(Box2d_PickAlgorithm_SE), theBox.P1(), sysLib::gl_pln_curve_info);
//	curves[2] = LineSegMaker(theBox.P1(), theBox.Corner(Box2d_PickAlgorithm_NW), sysLib::gl_pln_curve_info);
//	curves[3] = LineSegMaker(theBox.Corner(Box2d_PickAlgorithm_NW), theBox.P0(), sysLib::gl_pln_curve_info);
//
//	return std::move(curves);
//}
//
//AutLib::Pnt2d
//AutLib::singularityTools::FindParametricCoord
//(
//	const Entity2d_Polygon & thePoly, 
//	const Geom_Surface & theSurface,
//	const Standard_Real theLength
//)
//{
//	const auto& pts = thePoly.Points();
//
//	Standard_Real d = 0;
//	Pnt3d P0 = theSurface.Value(pts[0].X(), pts[0].Y());
//
//	forThose(Index, 1, pts.size() - 1)
//	{
//		Pnt3d P1 = theSurface.Value(pts[Index].X(), pts[Index].Y());
//
//		d += Distance(P0, P1);
//
//		if (d >= theLength)
//		{
//			return MEAN(pts[Index - 1], pts[Index]);
//		}
//
//		P0 = std::move(P1);
//	}
//
//	FatalErrorIn("Pnt2d FindParametricCoord()")
//		<< "Found no coord" << endl
//		<< abort(FatalError);
//	return pts[0];
//}
//
//std::shared_ptr<AutLib::Pln_Curve> 
//AutLib::singularityTools::GetPlnCurve(const Pnt2d & theP0, const Pnt2d & theP1)
//{
//	CadPlnModel_Segment LineSegMaker;
//
//	auto curve = LineSegMaker(theP0, theP1, sysLib::gl_pln_curve_info);
//	return std::move(curve);
//}