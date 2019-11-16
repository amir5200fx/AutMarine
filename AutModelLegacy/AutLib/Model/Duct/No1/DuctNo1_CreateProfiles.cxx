#include <Leg_Model_DuctNo1.hxx>

#include <Pnt2d.hxx>
#include <Leg_DuctNo1_Parameters.hxx>
#include <Leg_DuctNo1_HullForm.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_Line.hxx>

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom2d_BSplineCurve.hxx>

void AutLib::Leg_Model_DuctNo1::CreateBredthProfile()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto& breadth = Parameters()->Breadth();

	const auto OveralLength = dimensions.OveralLength()->Value();

	Pnt2d P0(0, dimensions.BreadthAtInlet()->Value());
	Pnt2d P14(OveralLength, dimensions.BreadthAtOutlet()->Value());

	const auto BreadthAtMid = 
		MEAN(dimensions.BreadthAtInlet()->Value(), dimensions.BreadthAtOutlet()->Value()) 
		* breadth.MidWidth()->Value();

	Pnt2d P7(Parameters()->Hull().MidLocation()->Value() * OveralLength, BreadthAtMid);

	Pnt2d P4(breadth.LeftTurningPosition()->Value() * P7.X(), BreadthAtMid + breadth.LeftTurningWidth()->Value() * (dimensions.BreadthAtInlet()->Value() - BreadthAtMid));
	Pnt2d P10(P7.X() + breadth.RightTurningPosition()->Value() * (OveralLength - P7.X()), BreadthAtMid + breadth.RightTurningWidth()->Value() * (dimensions.BreadthAtOutlet()->Value() - BreadthAtMid));

	Pnt2d P2(breadth.InletOffset()->Value() * 0.5 * P4.X(), P0.Y());
	Pnt2d P12(OveralLength - breadth.OutletOffset()->Value() * 0.5 * (P14.X() - P10.X()), P14.Y());

	Pnt2d P1 = MEAN(P0, P2);
	Pnt2d P13 = MEAN(P12, P14);

	Pnt2d P3(P2.X() + breadth.InletWeight()->Value() * (P4.X() - P2.X()), P2.Y());
	Pnt2d P11(P12.X() + breadth.OutletWeight()->Value() * (P10.X() - P12.X()), P12.Y());

	Pnt2d P6(P7.X() - breadth.MidOffset()->Value() * 0.5 * (P7.X() - P4.X()), P7.Y());
	Pnt2d P8(P7.X() + breadth.MidOffset()->Value() * 0.5 * (P10.X() - P7.X()), P7.Y());

	Pnt2d P5(P6.X() + breadth.InletRiseWeight()->Value() * (P4.X() - P6.X()), P6.Y());
	Pnt2d P9(P8.X() + breadth.OutletRiseWeight()->Value() * (P10.X() - P8.X()), P7.Y());

	Standard_Integer nbPoles = 15;

	TColgp_Array1OfPnt2d Points(1, 15);
	Points.SetValue(1, P0);
	Points.SetValue(2, P1);
	Points.SetValue(3, P2);
	Points.SetValue(4, P3);
	Points.SetValue(5, P4);
	Points.SetValue(6, P5);
	Points.SetValue(7, P6);
	Points.SetValue(8, P7);
	Points.SetValue(9, P8);
	Points.SetValue(10, P9);
	Points.SetValue(11, P10);
	Points.SetValue(12, P11);
	Points.SetValue(13, P12);
	Points.SetValue(14, P13);
	Points.SetValue(15, P14);

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = nbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 8);
	TColStd_Array1OfInteger Mults(1, 8);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, OveralLength / (Standard_Real)7);
	Knots.SetValue(3, (Standard_Real)2 * OveralLength / (Standard_Real)7);
	Knots.SetValue(4, (Standard_Real)3 * OveralLength / (Standard_Real)7);
	Knots.SetValue(5, (Standard_Real)4 * OveralLength / (Standard_Real)7);
	Knots.SetValue(6, (Standard_Real)5 * OveralLength / (Standard_Real)7);
	Knots.SetValue(7, (Standard_Real)6 * OveralLength / (Standard_Real)7);
	Knots.SetValue(8, OveralLength);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 2);
	Mults.SetValue(4, 2);
	Mults.SetValue(5, 2);
	Mults.SetValue(6, 2);
	Mults.SetValue(7, 2);
	Mults.SetValue(8, 3);

	Handle(Geom2d_BSplineCurve) BreadthCurve = 
		new Geom2d_BSplineCurve(Points, Weights, Knots, Mults, Degree);
	Breadth = BreadthCurve;
}

void AutLib::Leg_Model_DuctNo1::CreateDepthProfile()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto& depth = Parameters()->Depth();

	const auto OveralLength = dimensions.OveralLength()->Value();

	Pnt2d P0(0, dimensions.DepthAtInlet()->Value());
	Pnt2d P14(OveralLength, dimensions.DepthAtOutlet()->Value());

	Standard_Real DepthAtMid = MEAN(dimensions.DepthAtInlet()->Value(), dimensions.DepthAtOutlet()->Value()) * depth.MidWidth()->Value();

	Pnt2d P7(Parameters()->Hull().MidLocation()->Value() * OveralLength, DepthAtMid);

	Pnt2d P4(depth.LeftTurningPosition()->Value() * P7.X(), DepthAtMid + depth.LeftTurningWidth()->Value() * (dimensions.DepthAtInlet()->Value() - DepthAtMid));
	Pnt2d P10(P7.X() + depth.RightTurningPosition()->Value() * (OveralLength - P7.X()), DepthAtMid + depth.RightTurningWidth()->Value() * (dimensions.DepthAtOutlet()->Value() - DepthAtMid));

	Pnt2d P2(depth.InletOffset()->Value() * 0.5 * P4.X(), P0.Y());
	Pnt2d P12(OveralLength - depth.OutletOffset()->Value() * 0.5 * (P14.X() - P10.X()), P14.Y());

	Pnt2d P1 = MEAN(P0, P2);
	Pnt2d P13 = MEAN(P12, P14);

	Pnt2d P3(P2.X() + depth.InletWeight()->Value() * (P4.X() - P2.X()), P2.Y());
	Pnt2d P11(P12.X() + depth.OutletWeight()->Value() * (P10.X() - P12.X()), P12.Y());

	Pnt2d P6(P7.X() - depth.MidOffset()->Value() * 0.5 * (P7.X() - P4.X()), P7.Y());
	Pnt2d P8(P7.X() + depth.MidOffset()->Value() * 0.5 * (P10.X() - P7.X()), P7.Y());

	Pnt2d P5(P6.X() + depth.InletRiseWeight()->Value() * (P4.X() - P6.X()), P6.Y());
	Pnt2d P9(P8.X() + depth.OutletRiseWeight()->Value() * (P10.X() - P8.X()), P7.Y());

	Standard_Integer nbPoles = 15;

	TColgp_Array1OfPnt2d Points(1, 15);
	Points.SetValue(1, P0);
	Points.SetValue(2, P1);
	Points.SetValue(3, P2);
	Points.SetValue(4, P3);
	Points.SetValue(5, P4);
	Points.SetValue(6, P5);
	Points.SetValue(7, P6);
	Points.SetValue(8, P7);
	Points.SetValue(9, P8);
	Points.SetValue(10, P9);
	Points.SetValue(11, P10);
	Points.SetValue(12, P11);
	Points.SetValue(13, P12);
	Points.SetValue(14, P13);
	Points.SetValue(15, P14);

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = nbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 8);
	TColStd_Array1OfInteger Mults(1, 8);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, OveralLength / (Standard_Real)7);
	Knots.SetValue(3, (Standard_Real)2 * OveralLength / (Standard_Real)7);
	Knots.SetValue(4, (Standard_Real)3 * OveralLength / (Standard_Real)7);
	Knots.SetValue(5, (Standard_Real)4 * OveralLength / (Standard_Real)7);
	Knots.SetValue(6, (Standard_Real)5 * OveralLength / (Standard_Real)7);
	Knots.SetValue(7, (Standard_Real)6 * OveralLength / (Standard_Real)7);
	Knots.SetValue(8, OveralLength);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 2);
	Mults.SetValue(4, 2);
	Mults.SetValue(5, 2);
	Mults.SetValue(6, 2);
	Mults.SetValue(7, 2);
	Mults.SetValue(8, 3);

	Handle(Geom2d_BSplineCurve) DepthCurve = 
		new Geom2d_BSplineCurve(Points, Weights, Knots, Mults, Degree);
	Depth = DepthCurve;
}

void AutLib::Leg_Model_DuctNo1::CreateProfiles()
{
	CreateBredthProfile();

	CreateDepthProfile();
}