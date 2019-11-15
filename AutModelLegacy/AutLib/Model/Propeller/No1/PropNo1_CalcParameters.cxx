#include <Leg_Model_PropNo1.hxx>

#include <GeoProcessor.hxx>
#include <Leg_PropNo1_Parameters.hxx>
#include <Leg_PropNo1_Profiles.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

void AutLib::Leg_Model_PropNo1_Blade::CalcXSections()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	const auto dia = params.Diameter()->Value();
	const auto two = (Standard_Real)2.0;

	const auto tipRadius = (dia / two - params.TipGap()->Value()*dia / two);
	const auto dx = (tipRadius - params.HubRadius()->Value()) / (Standard_Real)(nbSections - 1);

	auto& X = Xparams()->xXCoords;

	Standard_Integer k = 0;
	for (auto& x : X)
	{
		x = k * dx + params.HubRadius()->Value();

		k++;
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	const auto& curve = Profiles()->Pitch;

	//const auto P0 = curve->Value(curve->FirstParameter());
	//const auto Pn = curve->Value(curve->LastParameter());

	const auto& xCoords = Xparams()->xXCoords;
	auto& X = Xparams()->xPitchAngle;

	//X[0] = Processor::DegToRadian(P0.Y());

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		auto xSection = xCoords[Index];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(curve, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " Found no intersection" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		X[Index] = Processor::DegToRadian(Point.Y());
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CalcXSkew()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	const auto& curve = Profiles()->Skew;

	//const auto P0 = curve->Value(curve->FirstParameter());
	//const auto Pn = curve->Value(curve->LastParameter());

	const auto& xCoords = Xparams()->xXCoords;
	auto& X = Xparams()->xSkew;

	//X[0] = Processor::DegToRadian(P0.Y());

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		auto xSection = xCoords[Index];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(curve, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " Found no intersection" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		X[Index] = Point.Y();
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CalcXChord()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	const auto& curve = Profiles()->Chord;

	//const auto P0 = curve->Value(curve->FirstParameter());
	//const auto Pn = curve->Value(curve->LastParameter());

	const auto& xCoords = Xparams()->xXCoords;
	auto& X = Xparams()->xChord;

	//X[0] = Processor::DegToRadian(P0.Y());

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		auto xSection = xCoords[Index];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(curve, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " Found no intersection" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		X[Index] = Point.Y();
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CalcXCamber()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	const auto& curve = Profiles()->Camber;

	//const auto P0 = curve->Value(curve->FirstParameter());
	//const auto Pn = curve->Value(curve->LastParameter());

	const auto& xCoords = Xparams()->xXCoords;
	auto& X = Xparams()->xMaxCamber;
	auto& Xpos = Xparams()->xMaxCamberPosition;

	//X[0] = Processor::DegToRadian(P0.Y());

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		auto xSection = xCoords[Index];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(curve, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " Found no intersection" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		X[Index] = Point.Y();
		Xpos[Index] = 0.4;
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CalcXThickness()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	const auto& curve = Profiles()->Thickness;

	//const auto P0 = curve->Value(curve->FirstParameter());
	//const auto Pn = curve->Value(curve->LastParameter());

	const auto& xCoords = Xparams()->xXCoords;
	auto& X = Xparams()->xThickness;

	//X[0] = Processor::DegToRadian(P0.Y());

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		auto xSection = xCoords[Index];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(curve, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " Found no intersection" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		X[Index] = Point.Y();
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CalcXRake()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	const auto& curve = Profiles()->Rake;

	//const auto P0 = curve->Value(curve->FirstParameter());
	//const auto Pn = curve->Value(curve->LastParameter());

	const auto& xCoords = Xparams()->xXCoords;
	auto& X = Xparams()->xRake;

	//X[0] = Processor::DegToRadian(P0.Y());

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		auto xSection = xCoords[Index];

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(xSection, 0), gp_Dir2d(0, 1));

		Intersection.Init(curve, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " Found no intersection" << endl
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			FatalErrorIn("void AutLib::Leg_Model_PropNo1_Blade::CalcXPitch()")
				<< " More than one intersection point has been found" << endl
				<< abort(FatalError);
		}

		Point = Intersection.Point(1);

		X[Index] = Point.Y();
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CalcXParameters()
{
	CalcXSections();

	CalcXPitch();

	CalcXSkew();

	CalcXChord();

	CalcXCamber();

	CalcXThickness();

	CalcXRake();
}