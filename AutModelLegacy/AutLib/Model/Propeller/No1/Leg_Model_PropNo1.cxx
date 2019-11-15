#include <Leg_Model_PropNo1.hxx>

#include <Leg_PropNo1_Parameters.hxx>
#include <Leg_PropNo1_Profiles.hxx>
#include <Leg_Prop_BladeFace.hxx>
#include <Leg_Prop_WrappedSection.hxx>
#include <Leg_Prop_PropView.hxx>

#include <TColgp_Array2OfPnt.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <Geom_BSplineSurface.hxx>

void AutLib::Leg_Model_PropNo1_Blade::AllocateMemory()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	theXparams_ = std::make_shared<Leg_PropNo1_Xparams>();
	theXparams_->AllocateMemory(nbSections);

	thePropView_ = std::make_shared<Leg_Prop_PropView>(nbSections);
}

AutLib::Leg_Model_PropNo1_Blade::Leg_Model_PropNo1_Blade()
{
	theParameters_ = std::make_shared<Leg_PropNo1_Parameters>();
	theProfiles_ = std::make_shared<Leg_PropNo1_Profile>();

	Leg_Model_EntitySystem::System() = 
		gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
}

void AutLib::Leg_Model_PropNo1_Blade::CreateBladeFaces()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();
	const auto nbSpans = params.NbSpans();

	auto bladeFaces = std::make_shared<Leg_Prop_BladeFace>();

	TColgp_Array2OfPnt Q(1, nbSections, 1, nbSpans);
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		Get_Const_Object(Wrapped) = *thePropView_->Wrapped(Index);
		forThose(J, 0, nbSpans - 1)
		{
			Q.SetValue(Index + 1, J + 1, Wrapped.Face(J));
		}
	}

	GeomAPI_PointsToBSplineSurface Interpolation;
	Interpolation.Interpolate(Q);

	Debug_If_Condition_Message(NOT Interpolation.IsDone(), "interpolation is not performed");

	bladeFaces->SetFace(Interpolation.Surface());

	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		Get_Const_Object(Wrapped) = *thePropView_->Wrapped(Index);
		forThose(J, 0, nbSpans - 1)
			Q.SetValue(Index + 1, J + 1, Wrapped.Back(J));
	}

	Interpolation.Interpolate(Q);

	Debug_If_Condition_Message(NOT Interpolation.IsDone(), "interpolation is not performed");

	bladeFaces->SetBack(Interpolation.Surface());

	theBlade_ = bladeFaces;
}

#include <Geom_Curve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <TopLoc_Location.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_CompSolid.hxx>
#include <TopoDS_Builder.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRep_Tool.hxx>
#include <TColGeom_Array1OfBSplineCurve.hxx>

void AutLib::Leg_Model_PropNo1_Blade::MakeFace()
{
	if (NOT Blade())
	{
		FatalErrorIn("void MakeFace()")
			<< "Found no blade" << endl
			<< abort(FatalError);
	}

	auto face = BRepBuilderAPI_MakeFace(Blade()->Face(), 1.0E-4);
	auto back = BRepBuilderAPI_MakeFace(Blade()->Back(), 1.0E-4);

	theFace_ = face;
	theBack_ = back;

	TopoDS_Compound Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompound(Compound);

	Builder.Add(Compound, face);
	Builder.Add(Compound, back);

	Leg_Model_Entity::ChangeEntity() = Compound;
}

void AutLib::Leg_Model_PropNo1_Blade::MakeClosed()
{
	theClosed_ = BRepAlgoAPI_Fuse(theFace_, theBack_);
	TColGeom_Array1OfBSplineCurve Curves(1, 8);

	Standard_Integer K = 0;
	for (
		TopExp_Explorer Explorer(theClosed_, TopAbs_EDGE);
		Explorer.More();
		Explorer.Next()
		)
	{
		auto Edge = TopoDS::Edge(Explorer.Current());
		TopLoc_Location Loc;
		Standard_Real First, Last;
		Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, First, Last);

		auto BSplCurve = Handle(Geom_BSplineCurve)::DownCast(Curve);
		Debug_Null_Pointer(BSplCurve);

		Curves.SetValue(++K, BSplCurve);
	}

	GeomFill_BSplineCurves Root(Curves.Value(1), Curves.Value(5), GeomFill_CoonsStyle);
	theClosed_ = BRepAlgoAPI_Fuse(theClosed_, BRepBuilderAPI_MakeFace(Root.Surface(), 1.0E-4));

	GeomFill_BSplineCurves TE(Curves.Value(3), Curves.Value(7), GeomFill_CoonsStyle);
	theClosed_ = BRepAlgoAPI_Fuse(theClosed_, BRepBuilderAPI_MakeFace(TE.Surface(), 1.0E-4));

	GeomFill_BSplineCurves Tip(Curves.Value(4), Curves.Value(8), GeomFill_CoonsStyle);
	theClosed_ = BRepAlgoAPI_Fuse(theClosed_, BRepBuilderAPI_MakeFace(Tip.Surface(), 1.0E-4));

	theClosed_.Reverse();

	Leg_Model_Entity::ChangeEntity() = theClosed_;
}

void AutLib::Leg_Model_PropNo1_Blade::Perform()
{
	AllocateMemory();

	CreateProfiles();
	
	CalcXParameters();

	CreateSections_NACA4Digits();

	CreateUnWrappedView();

	CreateWrappedView();

	CreateBladeFaces();

	Leg_Model_PropNo1_Blade::MakeFace();

	MakeClosed();

	Change_IsDone() = Standard_True;
}

void AutLib::Leg_Model_PropNo1_Blade::PerformToPreview()
{
	AllocateMemory();

	CreateProfiles();

	CalcXParameters();

	CreateSections_NACA4Digits();

	CreateUnWrappedView();

	CreateWrappedView();

	CreateBladeFaces();

	MakeFace();

	ChangePreviewEntity() = Entity();
}

#include <BRepBuilderAPI_Transform.hxx>

void AutLib::Leg_Model_PropNo1_Blades::MakeFace()
{
	const auto& params = *Parameters();
	const auto dTheta = 2 * M_PI / (Standard_Real)(params.NbBlades());

	TopoDS_Compound Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompound(Compound);

	theBlades_ = ClosedBlade();

	Builder.Add(Compound, theBlades_);

	forThose
	(
		Index,
		1,
		params.NbBlades() - 1
	)
	{
		auto Theta = Index * dTheta;

		gp_Trsf Rotate;
		Rotate.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), Theta);

		BRepBuilderAPI_Transform Transform(Rotate);
		Transform.Perform(theBlades_, Standard_True);

		Builder.Add(Compound, Transform.Shape());
	}

	theBlades_ = Compound;

	ChangeEntity() = theBlades_;
}

AutLib::Leg_Model_PropNo1_Blades::Leg_Model_PropNo1_Blades()
{
}

void AutLib::Leg_Model_PropNo1_Blades::PerformToPreview()
{
	AllocateMemory();

	CreateProfiles();

	CalcXParameters();

	CreateSections_NACA4Digits();

	CreateUnWrappedView();

	CreateWrappedView();

	CreateBladeFaces();

	Leg_Model_PropNo1_Blade::MakeFace();

	const auto& params = *Parameters();
	const auto dTheta = 2 * M_PI / (Standard_Real)(params.NbBlades());

	TopoDS_Compound Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompound(Compound);

	theBlades_ = Entity();

	Builder.Add(Compound, theBlades_);
	forThose
	(
		Index,
		1,
		params.NbBlades() - 1
	)
	{
		auto Theta = Index * dTheta;

		gp_Trsf Rotate;
		Rotate.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), Theta);

		BRepBuilderAPI_Transform Transform(Rotate);
		Transform.Perform(theBlades_, Standard_True);

		Builder.Add(Compound, Transform.Shape());
	}

	theBlades_ = Compound;

	ChangePreviewEntity() = theBlades_;
}

void AutLib::Leg_Model_PropNo1_Blades::Perform()
{
	Leg_Model_PropNo1_Blade::Perform();

	MakeFace();
}

#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>

void AutLib::Leg_Model_PropNo1::Perform()
{
	Leg_Model_PropNo1_Blades::Perform();

	MakeHub();

	BRepOffsetAPI_Sewing Sewing1;
	Sewing1.Add(Blades());
	Sewing1.Perform();

	auto Sewed1 = Sewing1.SewedShape();
	TopoDS_CompSolid Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompSolid(Compound);

	for (TopExp_Explorer Explorer(Sewed1, TopAbs_SHELL); Explorer.More(); Explorer.Next())
	{
		TopoDS_Shell Shell = TopoDS::Shell(Explorer.Current());

		BRepBuilderAPI_MakeSolid brep_solid(Shell);
		TopoDS_Solid Solid = brep_solid.Solid();

		Builder.Add(Compound, Solid);

		//myModel_ = BRepAlgoAPI_Fuse(Solid, myModel_);
	}

	BRepOffsetAPI_Sewing Sewing2;
	Sewing2.Add(theHub_);
	Sewing2.Perform();

	TopoDS_Shape Sewed2 = Sewing2.SewedShape();

	BRepBuilderAPI_MakeSolid brep_solid2(TopoDS::Shell(Sewed2));

	ChangeEntity() = BRepAlgoAPI_Fuse(Compound, brep_solid2.Solid());
}