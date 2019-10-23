#include <Leg_Vessel_Nihad2.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Leg_Nihad2_Dim.hxx>
#include <Entity_Line.hxx>
#include <Entity2d_LineRef.hxx>

namespace AutLib
{

	static void Assemble_Nihad2
	(
		const Standard_Real xSection,
		const std::vector<Pnt2d>& Points,
		Leg_Model_SectionCtrlPts& Section
	)
	{
		auto& ctrls = Section.Points();
		ctrls.reserve(Points.size());
		for (auto& x : Points)
		{
			ctrls.push_back(Pnt3d(xSection, x.X(), x.Y()));
		}
	}

	static std::vector<Pnt2d> UniformDiscretLine_Nihad2
	(
		const Pnt2d& P0,
		const Pnt2d& P1,
		const Standard_Integer NbSegments
	)
	{
		std::vector<Pnt2d> Points(NbSegments + 1);

		Standard_Real du = (Standard_Real)1. / (Standard_Real)NbSegments;
		Standard_Integer Index = 0;
		for (auto& x : Points)
		{
			x = P0 + (Standard_Real)Index * du * (P1 - P0);
			Index++;
		}
		return std::move(Points);
	}
}

std::shared_ptr<AutLib::Leg_Model_SectionCtrlPts> 
AutLib::Leg_Nihad2_HullPatch::CreateRawSection
(
	const Standard_Integer Section,
	const Standard_Real theTrimm,
	const Standard_Real theTightness1,
	const Standard_Real theTightness2
)
{
	auto xSection = xXCoords[Section];
	auto zSection = xZCoords[Section];
	auto SideSlope = xSideSlope[Section];
	auto DeadRise = xDeadRise[Section];
	auto Width = xYCoords[Section];
	auto Height = xDepth[Section] - zSection;

	auto MaxSideSlope = atan(Leg_Nihad2::MAX_SIDESLOPE_COEFF * Width / Height);
	auto SideSlopeAngle = SideSlope * MaxSideSlope;

	xSideSlopeAngle[Section] = SideSlopeAngle;

	Pnt2d P0(0, zSection);
	Pnt2d P8(Width, zSection + Height);

	auto MaxDeadRiseHeight = Leg_Nihad2::MAX_DEADRISE_COEFF * Height;
	auto MaxDeadRiseAngle = atan(MaxDeadRiseHeight / Width);

	Dir2d t0(cos(DeadRise * MaxDeadRiseAngle), sin(DeadRise * MaxDeadRiseAngle));
	Dir2d t8(-sin(SideSlopeAngle), -cos(SideSlopeAngle));

	Entity2d_LineRef Line0(P0, t0);
	Entity2d_LineRef Line2(P8, t8);

	auto IP = gProcessor::Intersect(Line0, Line2, (Standard_Real)1.0E-12);

	auto P2 = IP + theTrimm * (P0 - IP);
	auto P6 = IP + theTrimm * (P8 - IP);
	auto P4 = MEAN(P2, P6);

	auto Pm1 = MEAN(P2, P0);
	auto Pm2 = MEAN(P6, P8);

	auto it1 = (1.0 - theTightness1);
	auto it2 = (1.0 - theTightness2);

	auto P1 = P2 + it1 * (Pm1 - P2);
	auto P3 = P2 + it1 * (P4 - P2);

	auto P7 = P6 + it2 * (Pm2 - P6);
	auto P5 = P6 + it2 * (P4 - P6);

	auto Corner = 5;

	std::vector<Pnt2d> Pts;
	Pts.reserve(9);

	Pts.push_back(std::move(P0));
	Pts.push_back(std::move(P1));
	Pts.push_back(std::move(P2));
	Pts.push_back(std::move(P3));
	Pts.push_back(std::move(P4));
	Pts.push_back(std::move(P5));
	Pts.push_back(std::move(P6));
	Pts.push_back(std::move(P7));
	Pts.push_back(std::move(P8));

	auto newSection = 
		std::make_shared<Leg_Model_CorneredSectionCtrlPts>();
	Assemble_Nihad2
	(
		xSection,
		Pts, 
		*newSection
	);

	newSection->Corner() = Corner;

	return std::move(newSection);
}

std::shared_ptr<AutLib::Leg_Model_SectionCtrlPts> 
AutLib::Leg_Nihad2_HullPatch::CreateRawStem() const
{
	auto Section = NbNetColumns() - 1;

	auto xSection = xXCoords[Section];
	auto Width = (Standard_Real)0.0;
	auto Height = DepthAtBow()->Value();

	Pnt2d P0;
	Pnt2d P1((Standard_Real)0.0, Height);

	const auto nbRows = (Standard_Integer)9;
	auto MaxPoints = nbRows - 1;

	std::vector<Pnt2d> Points = UniformDiscretLine_Nihad2
	(
		P0,
		P1,
		MaxPoints - 1
	);

	auto newSection = std::make_shared<Leg_Model_SectionCtrlPts>();
	Assemble_Nihad2
	(
		xSection,
		Points,
		*newSection
	);

	return std::move(newSection);
}

std::shared_ptr<AutLib::Leg_Model_SectionCtrlPts> 
AutLib::Leg_Nihad2_HullPatch::CreateRawStemPaired()
{
	auto Section = NbNetColumns() - 2;

	auto xSection = xXCoords[Section];
	auto ySection = xYCoords[Section];
	auto SideSlope = xSideSlope[Section];
	auto Height = DepthAtBow()->Value();

	auto MaxSideSlope = atan(Leg_Nihad2::MAX_SIDESLOPE_COEFF * ySection / Height);
	auto SideSlopeAngle = SideSlope * MaxSideSlope;

	xSideSlopeAngle[Section] = SideSlopeAngle;

	auto dy = tan(SideSlopeAngle) * Height;
	auto y0 = MIN(ySection, ySection - dy);

	y0 = MAX(y0, ySection * Leg_Nihad2::MIN_DIST_COEFF);

	Pnt2d P0(y0, (Standard_Real)0.0);
	Pnt2d P1(ySection, Height);

	const auto nbRows = (Standard_Integer)9;
	auto MaxPoints = nbRows - 1;

	std::vector<Pnt2d> Points = UniformDiscretLine_Nihad2(P0, P1, MaxPoints - 1);

	auto newSection = std::make_shared<Leg_Model_CorneredSectionCtrlPts>();
	Assemble_Nihad2
	(
		xSection,
		Points,
		*newSection
	);
	newSection->Corner() = 1;

	return std::move(newSection);
}

void AutLib::Leg_Nihad2_HullPatch::CreateRawSections()
{
	const Leg_Nihad2_Dimensions& dimensions = *this;

	auto NbSections = dimensions.NbNetColumns();

	forThose
	(
		Section,
		0,
		NbSections - 3
	)
	{
		SetSection
		(
			Section,
			CreateRawSection(Section, xTrim[Section], xTightness0[Section], xTightness1[Section])
		);
	}

	SetSection(NbSections - 2, CreateRawStemPaired());
	SetSection(NbSections - 1, CreateRawStem());
}