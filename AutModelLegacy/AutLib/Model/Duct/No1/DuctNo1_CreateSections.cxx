#include <Leg_Model_DuctNo1.hxx>

#include <Pnt2d.hxx>
#include <Leg_DuctNo1_Parameters.hxx>

#include <BSplCLib.hxx>
#include <Geom_BSplineSurface.hxx>

namespace AutLib
{
	namespace Leg_DuctNo1
	{

		static void Assemble
		(
			Standard_Real xSection,
			const std::vector<Pnt2d>& Points,
			Leg_Model_SectionCtrlPts& Section
		)
		{
			auto& Pts = Section.Points();
			Pts.resize(Points.size());

			forThose
			(
				Index,
				0,
				Pts.size() - 1
			)
			{
				Pts[Index].X() = xSection;
				Pts[Index].Y() = Points[Index].X();
				Pts[Index].Z() = Points[Index].Y();
			}
		}

		static std::vector<Pnt2d> UniformDiscretLine
		(
			const Pnt2d& P0,
			const Pnt2d& P1,
			const Standard_Integer NbSegments
		)
		{
			std::vector<Pnt2d> Points(NbSegments + 1);

			const Standard_Real du = (Standard_Real)1.0 / (Standard_Real)NbSegments;

			forThose
			(
				Index,
				0,
				NbSegments
			)
			{
				Points[Index] = P0 + (Standard_Real)Index * du * (P1 - P0);
			}
			return std::move(Points);
		}

		static void UniformSurfaceMeshParameters
		(
			const Standard_Integer nI,
			std::vector<Standard_Real>& uKnots
		)
		{
			if (uKnots.size() != nI)
			{
				uKnots.resize(nI);
			}

			if (nI < 2)
			{
				FatalErrorIn(FunctionSIG)
					<< " Invalid Nb. of Control points in U direction" << endl
					<< abort(FatalError);
			}

			const Standard_Real du = (Standard_Real)1.0 / (Standard_Real)(nI - 1);
			uKnots[0] = (Standard_Real)0.0;

			forThose
			(
				Index,
				1,
				nI - 2
			)
			{
				uKnots[Index] = (Standard_Real)Index * du;
			}
			uKnots[nI - 1] = (Standard_Real)1.0;
		}

		static void CalcNbControlPoints
		(
			Standard_Real Width,
			Standard_Real Height,
			Standard_Integer MaxPoints,
			Standard_Integer& NbWidth,
			Standard_Integer& NbHeight
		)
		{
			Standard_Integer Reserved = 3;

			MaxPoints -= Reserved;

			if (MaxPoints < 2)
			{
				FatalErrorIn(FunctionSIG)
					<< " Invalid Nb. of control points" << endl
					<< abort(FatalError);
			}

			if (Height > Width)
			{
				NbWidth = (Standard_Integer)((Width / (Width + Height)) * (Standard_Real)MaxPoints);

				NbHeight = MaxPoints - NbWidth;
			}
			else
			{
				NbHeight = (Standard_Integer)((Height / (Width + Height)) * (Standard_Real)MaxPoints);

				NbWidth = MaxPoints - NbHeight;
			}
		}

		static void UniformDistributionPoints
		(
			const Pnt2d& P0,
			const Pnt2d& P1,
			const Pnt2d& P2,
			Standard_Integer NbWidth,
			Standard_Integer NbHeight,
			Standard_Integer MaxPoints,
			Standard_Integer& Corner,
			std::vector<Pnt2d>& Points
		)
		{
			Standard_Integer
				K = 0;

			if (Points.size() != MaxPoints)
			{
				Points.resize(MaxPoints);
			}

			std::vector<Pnt2d> Inner;

			Inner = UniformDiscretLine
			(
				P0,
				P1,
				NbWidth + 1
			);

			forThose
			(
				Index,
				0,
				NbWidth + 1
			)
			{
				Points[K++] = Inner[Index];
			}

			Inner = UniformDiscretLine
			(
				P1,
				P2,
				NbHeight + 1
			);

			forThose
			(
				Index,
				1,
				NbHeight + 1
			)
			{
				Points[K++] = Inner[Index];
			}
		}

		static void SequenceKnots
		(
			const Standard_Integer Degree,
			const Standard_Integer MaxIndex,
			const std::vector<Standard_Real>& Parameters,
			std::vector<Standard_Real>& Knots
		)
		{
			Standard_Integer m = Degree + MaxIndex + 1;

			forThose
			(
				Index,
				0,
				Degree
			)
				Knots[Index] = (Standard_Real)0.0;

			forThose
			(
				Index,
				m - Degree,
				m
			)
				Knots[Index] = (Standard_Real)1.0;

			Standard_Real InvDegree = (Standard_Real)1.0 / (Standard_Real)Degree;

			forThose
			(
				Index,
				1,
				MaxIndex - Degree
			)
			{
				Standard_Real Sigma = (Standard_Real)0.0;

				forThose(i, Index, Index + Degree - 1)
					Sigma += Parameters[i];

				Knots[Index + Degree] = InvDegree * Sigma;
			}
		}
	}
}

std::shared_ptr<AutLib::Leg_Model_SectionCtrlPts> 
AutLib::Leg_Model_DuctNo1::CreateSection
(
	const Standard_Integer Section
) const
{
	Standard_Real
		xSection,
		SideSlope,
		Width,
		Breadth,
		Depth,
		UpperTightness,
		LowerTightness,
		zSection;

	xSection = xXCoords[Section];
	zSection = xZCoords[Section];

	SideSlope = xSideSlope[Section];

	Width = xWidth[Section];
	Breadth = xYCoords[Section] / 2;
	Depth = xDepth[Section];

	Pnt2d P0(0, zSection);
	Pnt2d P5(Breadth, zSection + 0.5 * Depth);
	Pnt2d P10(0, zSection + Depth);

	Standard_Real t0 = -1 + SideSlope * 2;
	Pnt2d P3(P5.X() + t0 * P5.X(), zSection);
	Pnt2d P7(P5.X() - t0 * P5.X(), P10.Y());

	LowerTightness = xLowerTightness[Section];
	UpperTightness = xUpperTightness[Section];

	Pnt2d P2(P3.X() + LowerTightness * (P0.X() - P3.X()), P3.Y());
	Pnt2d P8(P7.X() + UpperTightness * (P10.X() - P7.X()), P7.Y());

	Pnt2d P1 = MEAN(P2, P0);
	Pnt2d P9 = MEAN(P8, P10);

	Pnt2d P4 = P3 + LowerTightness * (P5 - P3);
	Pnt2d P6 = P7 + UpperTightness * (P5 - P7);

	auto newSection = std::make_shared<Leg_Model_SectionCtrlPts>();
	auto& Coords = newSection->Points();
	Coords.resize(11);

	Coords[0] = Pnt3d(xSection, P0.X(), P0.Y());
	Coords[1] = Pnt3d(xSection, P1.X(), P1.Y());
	Coords[2] = Pnt3d(xSection, P2.X(), P2.Y());
	Coords[3] = Pnt3d(xSection, P3.X(), P3.Y());
	Coords[4] = Pnt3d(xSection, P4.X(), P4.Y());
	Coords[5] = Pnt3d(xSection, P5.X(), P5.Y());
	Coords[6] = Pnt3d(xSection, P6.X(), P6.Y());
	Coords[7] = Pnt3d(xSection, P7.X(), P7.Y());
	Coords[8] = Pnt3d(xSection, P8.X(), P8.Y());
	Coords[9] = Pnt3d(xSection, P9.X(), P9.Y());
	Coords[10] = Pnt3d(xSection, P10.X(), P10.Y());

	return std::move(newSection);
}

void AutLib::Leg_Model_DuctNo1::CreateSections()
{
	const auto& dimensions = Parameters()->Dimensions();

	const auto NbSections = dimensions.NbSections();

	auto& sections = ChangeSections();
	sections.resize(NbSections);

	forThose(Section, 0, NbSections - 1)
	{
		sections[Section] = CreateSection(Section);
	}
}

void AutLib::Leg_Model_DuctNo1::SetupPatch()
{
	std::vector<Standard_Real>
		uParameters;

	Standard_Integer
		uDegree,
		vDegree,
		uMaxIndex,
		vMaxIndex;

	const auto& dimensions = Parameters()->Dimensions();
	const auto nbSections = dimensions.NbSections();

	const Standard_Integer nbRows = 11;

	Leg_DuctNo1::UniformSurfaceMeshParameters
	(
		nbSections,
		uParameters
	);

	uDegree = 3;
	vDegree = 2;

	uMaxIndex = nbSections - 1;
	vMaxIndex = nbRows - 1;

	std::vector<Standard_Real>
		uKnots(uMaxIndex + uDegree + 2);

	Leg_DuctNo1::SequenceKnots
	(
		uDegree,
		uMaxIndex,
		uParameters,
		uKnots
	);

	TColStd_Array1OfReal Seq_uKnots(1, (Standard_Integer)uKnots.size());

	forThose(Index, 0, uKnots.size() - 1)
		Seq_uKnots.SetValue(Index + 1, uKnots[Index]);

	Standard_Integer uLength = BSplCLib::KnotsLength(Seq_uKnots);

	TColStd_Array1OfReal uKnotVector(1, uLength);
	TColStd_Array1OfReal vKnotVector(1, 6);
	TColStd_Array1OfInteger uMult(1, uLength);
	TColStd_Array1OfInteger vMult(1, 6);

	BSplCLib::Knots(Seq_uKnots, uKnotVector, uMult);
	//BSplCLib::Knots(Seq_vKnots, vKnotVector, vMult);

	vMult.SetValue(1, 3);
	vMult.SetValue(2, 2);
	vMult.SetValue(3, 2);
	vMult.SetValue(4, 2);
	vMult.SetValue(5, 2);
	vMult.SetValue(6, 3);

	vKnotVector.SetValue(1, 0);
	vKnotVector.SetValue(2, 0.2);
	vKnotVector.SetValue(3, 0.4);
	vKnotVector.SetValue(4, 0.6);
	vKnotVector.SetValue(5, 0.8);
	vKnotVector.SetValue(6, 1.0);

	theGeometry_ = 
		new Geom_BSplineSurface
	(
		*CtrlNet,
		*WeightNet,
		uKnotVector, 
		vKnotVector,
		uMult, vMult, uDegree, vDegree);
}