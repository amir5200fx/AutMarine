#include <Vessel_Station.hxx>

#include <Vessel_SingleStation.hxx>
#include <Marine_TableCurve.hxx>
#include <Marine_CompoundSection.hxx>

#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

namespace AutLib
{

	namespace marineLib
	{

		static std::vector<Pnt2d> 
			Intersection
			(
				const Handle(Geom2d_Line)& theLine,
				const std::shared_ptr<marineLib::cmpSectCurve>& theSection
			)
		{

			Geom2dAPI_InterCurveCurve Intersection;

			std::vector<Pnt2d> Pts;

			const auto& sections = theSection->Sections();
			for (const auto& x : sections)
			{
				Debug_Null_Pointer(x);
				const auto& cuvre = x->Curve();
				
				Intersection.Init(cuvre, theLine);

				if (Intersection.NbSegments())
				{
					Handle(Geom2d_Curve) C1, C2;
					Intersection.Segment(1, C1, C2);

					Pts.emplace_back(C1->Value(C1->FirstParameter()));
					Pts.emplace_back(C1->Value(C1->LastParameter()));

					Pts.emplace_back(C2->Value(C2->FirstParameter()));
					Pts.emplace_back(C2->Value(C2->LastParameter()));
				}

				if (Intersection.NbPoints())
				{
					forThose(Index, 1, Intersection.NbPoints())
					{
						Pts.emplace_back(Intersection.Point(Index));
					}
				}
			}

			return std::move(Pts);
		}
	}
}

AutLib::Vessel_Station::bounds 
AutLib::Vessel_Station::CalcBreadth
(
	const Standard_Real draft
) const
{
	Handle(Geom2d_Line) Line =
		new Geom2d_Line(gp_Pnt2d(0, draft), gp_Vec2d(1, 0));


}