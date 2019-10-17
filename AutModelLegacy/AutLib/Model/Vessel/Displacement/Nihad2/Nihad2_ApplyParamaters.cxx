#include <Leg_Vessel_Nihad2.hxx>

#include <Pnt2d.hxx>
#include <UnitSystem.hxx>

#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

void AutLib::Leg_Nihad2_HullPatch::ApplyRake()
{
	const Leg_Nihad2_Dimensions& dimension = *this;

	forThose
	(
		Section,
		0,
		dimension.NbNetColumns() - 1
	)
	{
		ApplyRake
		(
			*xSection[Section],
			xRake[Section]
		);
	}
}

void AutLib::Leg_Nihad2_HullPatch::ApplyForeFootShape()
{
	const Leg_Nihad2_Dimensions& dimensions = *this;
	const Leg_Nihad2_StemParams& Stem = *this;

	auto NbSections = dimensions.NbNetColumns();

	auto& ControlPoints1 = (*xSection[NbSections - 1]).Points();
	auto& ControlPoints3 = (*xSection[NbSections - 3]).Points();

	auto Root = ControlPoints1[0];

	auto P1 = ControlPoints1[1];
	auto P2 = ControlPoints3[0];

	auto NewP1 = Root + Stem.ForeFootShape()->Value() * (P1 - Root);
	auto NewP2 = Root + Stem.ForeFootShape()->Value() * (P2 - Root);

	ControlPoints1[1] = NewP1;

	ControlPoints1[0] = MEAN
	(
		NewP1,
		NewP2
	);

	Standard_Real
		dx,
		dz,
		zMax;

	dx = NewP2.X() - ControlPoints3[0].X();

	zMax = ControlPoints3[ControlPoints3.size() - 1].Z();

	forThose_Dec
	(
		Index,
		(Standard_Integer)ControlPoints3.size() - 2,
		0
	)
	{
		dz = zMax - ControlPoints3[Index].Z();

		ControlPoints3[Index].X() += (dz / zMax) * dx;
	}

	auto& ControlPoints2 = (*xSection[NbSections - 2]).Points();

	auto y1 = ControlPoints2[1].Y();

	ControlPoints2[0] = ControlPoints1[0];
	ControlPoints2[1] = ControlPoints1[1];

	ControlPoints2[1].Y() = y1;
	ControlPoints2[0].Y() = MEAN(ControlPoints3[1].Y(), y1);
}

void AutLib::Leg_Nihad2_HullPatch::ApplyParameters()
{
	ApplyRake();

	ApplyForeFootShape();
}

void AutLib::Leg_Nihad2_HullPatch::ApplyRake
(
	Leg_Model_SectionCtrlPts& theSection,
	const Standard_Real theRake
)
{
	auto NbPoints = (Standard_Integer)theSection.Points().size();
	auto& ControlPoints = theSection.Points();

	Standard_Real
		zSection,
		dx,
		dz;

	zSection = ControlPoints[NbPoints - 1].Z();

	dx = zSection * tan((Standard_Real)ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad) * theRake);

	forThose_Dec
	(
		Row,
		NbPoints - 2,
		0
	)
	{
		dz = zSection - ControlPoints[Row].Z();
		ControlPoints[Row].X() -= (dz / zSection) * dx;
	}
}