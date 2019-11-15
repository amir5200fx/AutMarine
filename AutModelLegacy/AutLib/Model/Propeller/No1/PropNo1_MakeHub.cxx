#include <Leg_Model_PropNo1.hxx>

#include <Entity3d_Box.hxx>
#include <Leg_Prop_PropView.hxx>
#include <Leg_Prop_WrappedSection.hxx>
#include <Leg_PropNo1_Parameters.hxx>

#include <Geom_BSplineCurve.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Builder.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

void AutLib::Leg_Model_PropNo1::MakeHub()
{
	const auto& params = *Parameters();

	const auto& wrapped = PropView()->Wrapped(0);
	auto box = Entity3d_Box::BoundingBoxOf(wrapped->Back());

	const auto& Pb0 = box.P0();
	const auto& Pb1 = box.P1();

	box = box.OffSet(0.25*(Pb1.Z() - Pb0.Z()));

	TopoDS_Compound Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompound(Compound);

	const auto zmin = Pb0.Z();
	const auto zmax = Pb1.Z();
	const auto hubRadius = params.HubRadius()->Value() + 0.001*params.HubRadius()->Value();

	Pnt3d P0(hubRadius, 0, zmin);
	Pnt3d P1(hubRadius, 0, zmax);

	Standard_Integer NbPoles = 2;
	Standard_Integer Degree = 1;

	TColgp_Array1OfPnt Poles0(1, NbPoles);
	Poles0.SetValue(1, P0);
	Poles0.SetValue(2, P1);

	TColStd_Array1OfReal Weights0(1, NbPoles);
	Weights0.Init(1);

	TColStd_Array1OfReal Knots0(1, 2);
	Knots0.SetValue(1, 0);
	Knots0.SetValue(2, 1);

	TColStd_Array1OfInteger Mults0(1, 2);
	Mults0.SetValue(1, 2);
	Mults0.SetValue(2, 2);

	Handle(Geom_BSplineCurve) Curve0 = new Geom_BSplineCurve(Poles0, Weights0, Knots0, Mults0, Degree);

	BRepPrimAPI_MakeRevolution Rev0(Curve0, Curve0->FirstParameter(), Curve0->LastParameter(), 2 * M_PI);

	Builder.Add(Compound, Rev0.Face());

	Standard_Real X0 = 0;
	if (params.RemoveHubApex()) X0 = 0.1*hubRadius;

	NbPoles = 3;
	Degree = 2;

	Pnt3d P2(X0, 0, zmin - params.Hub().HubLength()->Value());
	Pnt3d P3(hubRadius, 0, zmin - params.Hub().HubLength()->Value());
	Pnt3d P4 = P0;

	P3 = P3 + params.Hub().HubWeight()->Value()*(P4 - P3);

	if (params.Hub().HubLength()->Value() > 0)
	{
		TColgp_Array1OfPnt Poles1(1, NbPoles);
		Poles1.SetValue(1, P2);
		Poles1.SetValue(2, P3);
		Poles1.SetValue(3, P4);

		TColStd_Array1OfReal Weights1(1, NbPoles);
		Weights1.Init(1);

		TColStd_Array1OfReal Knots1(1, 2);
		Knots1.SetValue(1, 0);
		Knots1.SetValue(2, 1);

		TColStd_Array1OfInteger Mults1(1, 2);
		Mults1.SetValue(1, 3);
		Mults1.SetValue(2, 3);

		Handle(Geom_BSplineCurve) Curve1 = new Geom_BSplineCurve(Poles1, Weights1, Knots1, Mults1, Degree);

		BRepPrimAPI_MakeRevolution Rev1(Curve1, Curve1->FirstParameter(), Curve1->LastParameter(), 2 * M_PI);

		Builder.Add(Compound, Rev1.Face());
	}

	Pnt3d P5 = P1;
	Pnt3d P6(params.Hub().ShaftRadius()->Value(), 0, zmax + params.Hub().ShaftOffset()->Value());

	NbPoles = 2;
	Degree = 1;

	TColgp_Array1OfPnt Poles2(1, NbPoles);
	Poles2.SetValue(1, P5);
	Poles2.SetValue(2, P6);

	TColStd_Array1OfReal Weights2(1, NbPoles);
	Weights2.Init(1);

	TColStd_Array1OfReal Knots2(1, 2);
	Knots2.SetValue(1, 0);
	Knots2.SetValue(2, 1);

	TColStd_Array1OfInteger Mults2(1, 2);
	Mults2.SetValue(1, 2);
	Mults2.SetValue(2, 2);

	Handle(Geom_BSplineCurve) Curve2 = new Geom_BSplineCurve(Poles2, Weights2, Knots2, Mults2, Degree);

	BRepPrimAPI_MakeRevolution Rev2(Curve2, Curve2->FirstParameter(), Curve2->LastParameter(), 2 * M_PI);

	Builder.Add(Compound, Rev2.Face());

	Pnt3d P7 = P6;
	Pnt3d P8(params.Hub().ShaftRadius()->Value(), 0, P7.Z() + params.Hub().ShaftLength()->Value());

	if (params.Hub().ShaftLength()->Value())
	{
		NbPoles = 2;
		Degree = 1;

		TColgp_Array1OfPnt Poles3(1, NbPoles);
		Poles3.SetValue(1, P7);
		Poles3.SetValue(2, P8);

		TColStd_Array1OfReal Weights3(1, NbPoles);
		Weights3.Init(1);

		TColStd_Array1OfReal Knots3(1, 2);
		Knots3.SetValue(1, 0);
		Knots3.SetValue(2, 1);

		TColStd_Array1OfInteger Mults3(1, 2);
		Mults3.SetValue(1, 2);
		Mults3.SetValue(2, 2);

		Handle(Geom_BSplineCurve) Curve3 = new Geom_BSplineCurve(Poles3, Weights3, Knots3, Mults3, Degree);

		BRepPrimAPI_MakeRevolution Rev3(Curve3, Curve3->FirstParameter(), Curve3->LastParameter(), 2 * M_PI);

		Builder.Add(Compound, Rev3.Face());
	}

	Pnt3d P9(0, 0, P8.Z());
	Pnt3d P10 = P8;

	NbPoles = 2;
	Degree = 1;

	TColgp_Array1OfPnt Poles4(1, NbPoles);
	Poles4.SetValue(1, P9);
	Poles4.SetValue(2, P10);

	TColStd_Array1OfReal Weights4(1, NbPoles);
	Weights4.Init(1);

	TColStd_Array1OfReal Knots4(1, 2);
	Knots4.SetValue(1, 0);
	Knots4.SetValue(2, 1);

	TColStd_Array1OfInteger Mults4(1, 2);
	Mults4.SetValue(1, 2);
	Mults4.SetValue(2, 2);

	Handle(Geom_BSplineCurve) Curve4 = new Geom_BSplineCurve(Poles4, Weights4, Knots4, Mults4, Degree);

	BRepPrimAPI_MakeRevolution Rev4(Curve4, Curve4->FirstParameter(), Curve4->LastParameter(), 2 * M_PI);

	Builder.Add(Compound, Rev4.Face());


	if (params.RemoveHubApex() AND params.Hub().HubLength()->Value() > 0)
	{
		Pnt3d P11 = P2;
		Pnt3d P12(0, 0, zmin - params.Hub().HubLength()->Value());

		NbPoles = 2;
		Degree = 1;

		TColgp_Array1OfPnt Poles5(1, NbPoles);
		Poles5.SetValue(1, P11);
		Poles5.SetValue(2, P12);

		TColStd_Array1OfReal Weights5(1, NbPoles);
		Weights5.Init(1);

		TColStd_Array1OfReal Knots5(1, 2);
		Knots5.SetValue(1, 0);
		Knots5.SetValue(2, 1);

		TColStd_Array1OfInteger Mults5(1, 2);
		Mults5.SetValue(1, 2);
		Mults5.SetValue(2, 2);

		Handle(Geom_BSplineCurve) Curve5 = new Geom_BSplineCurve(Poles5, Weights5, Knots5, Mults5, Degree);

		BRepPrimAPI_MakeRevolution Rev5(Curve5, Curve5->FirstParameter(), Curve5->LastParameter(), 2 * M_PI);

		Builder.Add(Compound, Rev5.Face());
	}

	if (params.Hub().HubLength()->Value() IS_EQUAL 0)
	{
		Pnt3d P11 = P0;
		Pnt3d P12(0, 0, zmin);

		NbPoles = 2;
		Degree = 1;

		TColgp_Array1OfPnt Poles5(1, NbPoles);
		Poles5.SetValue(1, P11);
		Poles5.SetValue(2, P12);

		TColStd_Array1OfReal Weights5(1, NbPoles);
		Weights5.Init(1);

		TColStd_Array1OfReal Knots5(1, 2);
		Knots5.SetValue(1, 0);
		Knots5.SetValue(2, 1);

		TColStd_Array1OfInteger Mults5(1, 2);
		Mults5.SetValue(1, 2);
		Mults5.SetValue(2, 2);

		Handle(Geom_BSplineCurve) Curve5 = new Geom_BSplineCurve(Poles5, Weights5, Knots5, Mults5, Degree);

		BRepPrimAPI_MakeRevolution Rev5(Curve5, Curve5->FirstParameter(), Curve5->LastParameter(), 2 * M_PI);

		Builder.Add(Compound, Rev5.Face());
	}

	theHub_ = Compound;
}