#include <Leg_Model_DuctNo1.hxx>

#include <Pnt2d.hxx>
#include <Leg_DuctNo1_Parameters.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

#define Interpd1(X, Val0, Val1)  \
   (Val1 - Val0)*X + Val0;

#define SmoothingParameter(XLIST, nbSections, WEIGHT, LEVEL)  \
   forThose(Index, 1, LEVEL) {Leg_DuctNo1::Smoothing(XLIST, WEIGHT, nbSections);}

namespace AutLib
{
	namespace Leg_DuctNo1
	{
		static void Smoothing
		(
			std::vector<Standard_Real>& Parameters,
			Standard_Real Coeff,
			Standard_Integer nbSections
		)
		{
			Try_Exception_Handle_Exit
			(
				forThose
				(
					Section,
					1,
					nbSections - 2
				)
			{
				Standard_Real Mean = MEAN
				(
					Parameters[Section - 1],
					Parameters[Section + 1]
				);

				Parameters[Section] += (Mean - Parameters[Section]) * Coeff;
			}
			);
		}
	}
}

void AutLib::Leg_Model_DuctNo1::CalcxXSections()
{
	const auto& dimensions = Parameters()->Dimensions();

	auto& XCoords = xXCoords;

	const auto nbSections = dimensions.NbSections();

	const auto dx = dimensions.OveralLength()->Value() / (Standard_Real)(nbSections - 1);
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		auto Section = Index;
		XCoords[Section] = Index * dx;
	}
}

void AutLib::Leg_Model_DuctNo1::CalcxYSections()
{
	const auto& dimensions = Parameters()->Dimensions();

	if (Breadth.IsNull())
	{
		FatalErrorIn(" void AutLib::Leg_Model_DuctNo1::CalcxYSections()")
			<< " No Breadth Profile has been found" << endl
			<< abort(FatalError);
	}

	const auto nbSections = dimensions.NbSections();

	const auto& xSections = xXCoords;
	auto& YCoords = xYCoords;

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;

	forThose
	(
		Section,
		1,
		nbSections - 2
	)
	{
		Standard_Real X = xSections[Section];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(X, 0), gp_Dir2d(0, 1));

		Intersection.Init(Breadth, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn(" void AutLib::Leg_Model_DuctNo1::CalcxYSections()")
				<< " No Intersection has been found" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn(" void AutLib::Leg_Model_DuctNo1::CalcxYSections()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		YCoords[Section] = Point.Y();
	}

	xYCoords[0] = Breadth->Value(Breadth->FirstParameter()).Y();
	xYCoords[xYCoords.size() - 1] = Breadth->Value(Breadth->LastParameter()).Y();
}

void AutLib::Leg_Model_DuctNo1::CalcxZSections()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto& generator = Parameters()->Generator();

	const auto nbSections = dimensions.NbSections();

	const auto& XCoords = xXCoords;
	auto& ZCoords = xZCoords;

	Standard_Real Length = XCoords[nbSections - 1];

	Standard_Real
		XRise,
		XPos,
		XVel0,
		XVel1;

	XRise = generator.RisePoint()->Value() * Length;
	XPos = generator.Position()->Value() * Length;
	XVel0 = generator.OutletTangent()->Value() * XPos;
	XVel1 = XRise + generator.RiseTangent()->Value() * (XPos - XRise);

	Standard_Real
		Parameter,
		xSection;

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		xSection = XCoords[Section];

		if (xSection <= XVel0)
		{
			ZCoords[Section] = dimensions.HeightAtOutlet()->Value();
		}
		else if (xSection >= XVel1)
		{
			ZCoords[Section] = (Standard_Real)0.0;
		}
		else
		{
			Parameter = (xSection - XVel1) / (XVel0 - XVel1);

			Standard_Real Value = Interpd1
			(
				Parameter,
				(Standard_Real)0.0,
				dimensions.HeightAtOutlet()->Value()
			);

			ZCoords[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			ZCoords,
			nbSections,
			Leg_DuctNo1::SMOOTH_WEIGHT,
			Leg_DuctNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::Leg_Model_DuctNo1::CalcxDepth()
{
	const auto& dimensions = Parameters()->Dimensions();

	if (Depth.IsNull())
	{
		FatalErrorIn("void AutLib::Leg_Model_DuctNo1::CalcxDepth()")
			<< " No Depth Profile has been found" << endl
			<< abort(FatalError);
	}

	const auto nbSections = dimensions.NbSections();

	const auto& xSections = xXCoords;

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;

	forThose
	(
		Section,
		1,
		nbSections - 2
	)
	{
		Standard_Real X = xSections[Section];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(X, 0), gp_Dir2d(0, 1));

		Intersection.Init(Depth, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn("void AutLib::Leg_Model_DuctNo1::CalcxDepth()")
				<< " No Intersection has been found" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn("void AutLib::Leg_Model_DuctNo1::CalcxDepth()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		xDepth[Section] = Point.Y();
	}

	xDepth[0] = Depth->Value(Depth->FirstParameter()).Y();
	xDepth[xDepth.size() - 1] = Depth->Value(Depth->LastParameter()).Y();
}

void AutLib::Leg_Model_DuctNo1::CalcxUpperTightness()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto& hull = Parameters()->Hull();

	const auto& XCoords = xXCoords;
	auto& XTightness = xUpperTightness;

	const auto nbSections = dimensions.NbSections();

	auto Length = XCoords[nbSections - 1];

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = XCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * X,
				hull.Inlet().UpperTightness()->Value(),
				hull.Mid().UpperTightness()->Value()
			);

			XTightness[Section] = Value;
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				hull.Mid().UpperTightness()->Value(),
				hull.Outlet().UpperTightness()->Value()
			);

			XTightness[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			XTightness,
			nbSections,
			Leg_DuctNo1::SMOOTH_WEIGHT,
			Leg_DuctNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::Leg_Model_DuctNo1::CalcxLowerTightness()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto& hull = Parameters()->Hull();

	const auto& XCoords = xXCoords;
	auto& XTightness = xLowerTightness;

	const auto nbSections = dimensions.NbSections();

	const auto Length = XCoords[nbSections - 1];

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		auto X = XCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * X,
				hull.Inlet().LowerTightness()->Value(),
				hull.Mid().LowerTightness()->Value()
			);

			XTightness[Section] = Value;
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				hull.Mid().LowerTightness()->Value(),
				hull.Outlet().LowerTightness()->Value()
			);

			XTightness[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			XTightness,
			nbSections,
			Leg_DuctNo1::SMOOTH_WEIGHT,
			Leg_DuctNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::Leg_Model_DuctNo1::CalcxSideSlope()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto& hull = Parameters()->Hull();

	const auto& XCoords = xXCoords;
	auto& XSide = xSideSlope;

	const auto nbSections = dimensions.NbSections();

	const auto Length = dimensions.OveralLength()->Value();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		auto X = XCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			auto Value = Interpd1
			(
				(Standard_Real)2.0 * X,
				hull.Inlet().SideSlope()->Value(),
				hull.Mid().SideSlope()->Value()
			);

			XSide[Section] = Value;
		}
		else
		{
			auto Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				hull.Mid().SideSlope()->Value(),
				hull.Outlet().SideSlope()->Value()
			);

			XSide[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			XSide,
			nbSections,
			Leg_DuctNo1::SMOOTH_WEIGHT,
			Leg_DuctNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::Leg_Model_DuctNo1::CalcxWidth()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto& hull = Parameters()->Hull();

	const auto& XCoords = xXCoords;

	const auto nbSections = dimensions.NbSections();

	const auto Length = dimensions.OveralLength()->Value();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		auto X = XCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			auto Value = Interpd1
			(
				(Standard_Real)2.0 * X,
				hull.Inlet().Width()->Value(),
				hull.Mid().Width()->Value()
			);

			xWidth[Section] = Value;
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				hull.Mid().Width()->Value(),
				hull.Outlet().Width()->Value()
			);

			xWidth[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			xWidth,
			nbSections,
			Leg_DuctNo1::SMOOTH_WEIGHT,
			Leg_DuctNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::Leg_Model_DuctNo1::CalcxParameters()
{
	CalcxYSections();

	CalcxZSections();

	CalcxDepth();

	CalcxLowerTightness();

	CalcxUpperTightness();

	CalcxSideSlope();

	CalcxSideSlope();

	CalcxWidth();
}