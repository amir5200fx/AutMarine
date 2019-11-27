#include <Leg_Model_PropNo1.hxx>

#include <Pnt2d.hxx>
#include <GeoProcessor.hxx>
#include <Leg_PropNo1_Parameters.hxx>
#include <Leg_PropNo1_Profiles.hxx>

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom2d_BSplineCurve.hxx>

void AutLib::Leg_Model_PropNo1_Blade::CreatePitchProfile()
{
	const auto& params = *Parameters();

	Pnt2d P0, P1, P2;

	P0.SetCoord(params.HubRadius()->Value(), params.Blade().Pitch().RootPitch()->Value());
	P2.SetCoord(params.Diameter()->Value() / 2, params.Blade().Pitch().TipPitch()->Value());

	Pnt2d t0, t2;
	const auto dx = ABS(P2.X() - P0.X());
	const auto dy = ABS(P2.Y() - P0.Y());

	const auto theta0 = params.Blade().Pitch().RootSteep()->Value()*(atan(dx / dy));
	const auto theta2 = params.Blade().Pitch().TipSteep()->Value()*(atan(dy / dx));

	t0.X() = sin(theta0);
	t0.Y() = -cos(theta0);

	t2.X() = -cos(theta2);
	t2.Y() = sin(theta2);

	if (ABS(CrossProduct(t0, t2)) < EPS6)
	{
		P1 = (P0 + P2) / 2;
	}
	else
	{
		P1 = Processor::IntersectionTwoLines(P0, t0, P2, t2);
	}

	Standard_Integer NbPoles = 3;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	Handle(Geom2d_Curve) Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	Profiles()->Pitch = Curve;
}

void AutLib::Leg_Model_PropNo1_Blade::CreateChordProfile()
{
	const auto& params = *Parameters();

	Pnt2d P0, P1, P2, P3, P4;

	P0.SetCoord(params.HubRadius()->Value(), params.Blade().Chord().RootChord()->Value());
	P1.SetCoord(P0.X(), params.Blade().Chord().MaxChord()->Value());
	P2.SetCoord
	(
		params.Blade().Chord().MaxChordLocation()->Value()*
		(params.Diameter()->Value() / 2 - params.HubRadius()->Value())
		+ params.HubRadius()->Value()
		, params.Blade().Chord().MaxChord()->Value()
	);
	P3.SetCoord(params.Diameter()->Value() / 2, P2.Y());
	P4.SetCoord(P3.X(), params.Blade().Chord().TipChord()->Value());

	P1 = P1 + params.Blade().Chord().RootWeight()->Value()*(P2 - P1);

	Standard_Integer NbPoles = 5;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);
	Poles.SetValue(4, P3);
	Poles.SetValue(5, P4);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);
	//Weights.SetValue(2, params.BladeParameters().ChordForm().RootWeight());
	Weights.SetValue(4, params.Blade().Chord().TipWeight()->Value());

	TColStd_Array1OfReal Knots(1, 3);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.5);
	Knots.SetValue(3, 1);

	TColStd_Array1OfInteger Mults(1, 3);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 3);

	Handle(Geom2d_Curve) Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	Profiles()->Chord = Curve;
}

void AutLib::Leg_Model_PropNo1_Blade::CreateSkewProfile()
{
	const auto& params = *Parameters();

	Pnt2d P0, P1, P2;

	P0.SetX(params.HubRadius()->Value());
	P2.SetCoord(params.Diameter()->Value() / 2, params.Blade().Skew().TipSkew()->Value());

	Pnt2d t0, t2;
	const auto dx = ABS(P2.X() - P0.X());
	const auto dy = ABS(P2.Y() - P0.Y());

	const auto MaxTheta0 = atan(dy / dx);
	const auto MinTheta0 = -0.5*MaxTheta0;

	const auto theta0 = MinTheta0 + params.Blade().Skew().RootSteep()->Value()*(MaxTheta0 - MinTheta0);
	const auto theta2 = params.Blade().Skew().TipSteep()->Value()*(atan(dx / dy));

	t0.X() = cos(theta0);
	t0.Y() = sin(theta0);

	t2.X() = -sin(theta2);
	t2.Y() = -cos(theta2);

	if (ABS(CrossProduct(t0, t2)) < EPS6)
	{
		P1 = (P0 + P2) / 2;
	}
	else
	{
		P1 = Processor::IntersectionTwoLines(P0, t0, P2, t2);
	}

	Standard_Integer NbPoles = 3;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	Handle(Geom2d_Curve) Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	Profiles()->Skew = Curve;
}

void AutLib::Leg_Model_PropNo1_Blade::CreateCamberProfile()
{
	const auto& params = *Parameters();

	Pnt2d P0, P1, P2, P3, P4;

	P0.SetCoord(params.HubRadius()->Value(), params.Blade().Camber().RootCamber()->Value());
	P1.SetCoord(P0.X(), params.Blade().Camber().MaxCamber()->Value());
	P2.SetCoord(params.Blade().Camber().MaxCamberLocation()->Value()*(params.Diameter()->Value() / 2 - params.HubRadius()->Value()) + params.HubRadius()->Value(), P1.Y());
	P3.SetCoord(params.Diameter()->Value() / 2, P2.Y());
	P4.SetCoord(P3.X(), params.Blade().Camber().TipCamber()->Value());

	P1 = P1 + params.Blade().Camber().RootWeight()->Value()*(P2 - P1);

	Standard_Integer NbPoles = 5;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);
	Poles.SetValue(4, P3);
	Poles.SetValue(5, P4);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);
	//Weights.SetValue(2, params.BladeParameters().CamberForm().RootWeight());
	Weights.SetValue(4, params.Blade().Camber().TipWeight()->Value());

	TColStd_Array1OfReal Knots(1, 3);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.5);
	Knots.SetValue(3, 1);

	TColStd_Array1OfInteger Mults(1, 3);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 3);

	Handle(Geom2d_Curve) Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	Profiles()->Camber = Curve;
}

void AutLib::Leg_Model_PropNo1_Blade::CreateThicknessProfile()
{
	const auto& params = *Parameters();

	Pnt2d P0, P1, P2;

	P0.SetCoord(params.HubRadius()->Value(), params.Blade().Thickness().RootThickness()->Value());
	P2.SetCoord(params.Diameter()->Value() / 2, params.Blade().Thickness().TipThickness()->Value());

	Pnt2d t0, t2;
	Standard_Real dx = ABS(P2.X() - P0.X());
	Standard_Real dy = ABS(P2.Y() - P0.Y());

	Standard_Real theta0 = params.Blade().Thickness().RootSteep()->Value()*(atan(dx / dy));
	Standard_Real theta2 = params.Blade().Thickness().TipSteep()->Value()*(atan(dy / dx));

	t0.X() = sin(theta0);
	t0.Y() = -cos(theta0);

	t2.X() = -cos(theta2);
	t2.Y() = sin(theta2);

	if (ABS(CrossProduct(t0, t2)) < EPS6)
	{
		P1 = (P0 + P2) / 2;
	}
	else
	{
		P1 = Processor::IntersectionTwoLines(P0, t0, P2, t2);
	}

	Standard_Integer NbPoles = 3;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);
	Poles.SetValue(3, P2);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	Handle(Geom2d_Curve) Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	Profiles()->Thickness = Curve;
}

void AutLib::Leg_Model_PropNo1_Blade::CreateRakeProfile()
{
	const auto& params = *Parameters();

	Pnt2d P0, P1;
	P1.SetCoord(params.Diameter()->Value() / 2, params.Blade().Rake().TipRake()->Value());

	Standard_Integer NbPoles = 2;
	Standard_Integer Degree = 1;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, P0);
	Poles.SetValue(2, P1);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 2);
	Mults.SetValue(2, 2);

	Handle(Geom2d_Curve) Curve = new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
	Profiles()->Rake = Curve;
}

void AutLib::Leg_Model_PropNo1_Blade::CreateProfiles()
{
	CreatePitchProfile();

	CreateSkewProfile();

	CreateChordProfile();

	CreateCamberProfile();

	CreateThicknessProfile();

	CreateRakeProfile();
}