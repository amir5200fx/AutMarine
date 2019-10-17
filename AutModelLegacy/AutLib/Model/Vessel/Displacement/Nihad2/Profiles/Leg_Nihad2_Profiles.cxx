#include <Leg_Vessel_Nihad2.hxx>

#include <Leg_Nihad2_Dim.hxx>

#include <Pnt2d.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

void AutLib::Leg_Nihad2_HullPatch::CreateDeckProfile()
{
	const Leg_Nihad2_Dimensions& dimensions = *this;
	const Leg_Nihad2_HullParams& hull = *this;
	const Leg_Nihad2_TransomParams& transom = *this;
	const Leg_Nihad2_StemParams& stem = *this;

	Leg_Nihad2_Profile& profile = *this;

	Standard_Integer nbPoles = 7;
	TColgp_Array1OfPnt2d Points(1, nbPoles);

	Pnt2d P1 = Pnt2d(0, transom.Width()->Value() * dimensions.BeamOnDeck()->Value());
	Pnt2d P2 = Pnt2d(0, dimensions.BeamOnDeck()->Value());
	Pnt2d P4 = Pnt2d(hull.MaxAreaLocation()->Value() * dimensions.LengthOnDeck()->Value(), dimensions.BeamOnDeck()->Value());
	Pnt2d P6 = Pnt2d(dimensions.LengthOnDeck()->Value(), dimensions.BeamOnDeck()->Value());
	Pnt2d P7 = Pnt2d(dimensions.LengthOnDeck()->Value(), stem.BowRounding()->Value() * dimensions.BeamOnDeck()->Value());

	Pnt2d P3 = P4 + (P2 - P4) * hull.AftFullness()->Value();
	Pnt2d P5 = P4 + 0.95 * (P6 - P4) * hull.FwdFullness()->Value();

	Points.SetValue(1, P1);
	Points.SetValue(2, P2);
	Points.SetValue(3, P3);
	Points.SetValue(4, P4);
	Points.SetValue(5, P5);
	Points.SetValue(6, P6);
	Points.SetValue(7, P7);

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = nbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 4);
	TColStd_Array1OfInteger Mults(1, 4);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.25);
	Knots.SetValue(3, 0.75);
	Knots.SetValue(4, 1);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 2);
	Mults.SetValue(4, 3);

	profile.Deck =
		new Geom2d_BSplineCurve(Points, Weights, Knots, Mults, Degree);
}