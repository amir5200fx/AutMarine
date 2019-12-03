#include <Leg_Model_DuctNo1.hxx>

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Leg_DuctNo1_Parameters.hxx>

void AutLib::Leg_Model_DuctNo1::AllocateMemory()
{
	const auto& dimensions = Parameters()->Dimensions();
	const auto nbSections = dimensions.NbSections();
	const Standard_Integer nbRows = 11;

	Leg_DuctNo1_Xparams::AllocateMemory(nbSections);

	CtrlNet = std::make_shared<TColgp_Array2OfPnt>(1, nbSections, 1, nbRows);
	WeightNet = std::make_shared<TColStd_Array2OfReal>(1, nbSections, 1, nbRows);

	auto& Sections = ChangeSections();
	Sections.resize(nbSections);
}

void AutLib::Leg_Model_DuctNo1::SetupControlNet()
{
	if (NOT WeightNet)
	{
		FatalErrorIn("void AutLib::Leg_Model_DuctNo1::SetupControlNet()")
			<< " No weightNet has been allocated!" << endl
			<< abort(FatalError);
	}

	if (NOT CtrlNet)
	{
		FatalErrorIn("void AutLib::Leg_Model_DuctNo1::SetupControlNet()")
			<< " No ctrlNet has been allocated!" << endl
			<< abort(FatalError);
	}

	const auto& dimensions = Parameters()->Dimensions();
	const auto nbSections = dimensions.NbSections();
	static const Standard_Real sq2 = sqrt((Standard_Real)2.0) / (Standard_Real)2.0;

	const Standard_Integer nbRows = 11;

	Pnt3d Point;

	WeightNet->Init((Standard_Real)1.0);

	Standard_Integer i = 0;
	Standard_Integer j = 0;
	for (const auto& x : Sections())
	{
		Debug_Null_Pointer(x);

		j = 0;
		const auto& ctrlPts = x->Points();
		for (const auto& pt : ctrlPts)
		{
			CtrlNet->SetValue(i + 1, j + 1, pt);
			j++;
		}

		WeightNet->SetValue(i + 1, 4, sq2);
		WeightNet->SetValue(i + 1, 8, sq2);
		i++;
	}
	
}

#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Builder.hxx>
#include <Geom_BSplineSurface.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

void AutLib::Leg_Model_DuctNo1::MakeFace()
{
	auto model = BRepBuilderAPI_MakeFace(theGeometry_, 1.0E-4);

	gp_Ax2 A2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));

	auto Hull = Handle(Geom_BSplineSurface)::DownCast(theGeometry_);
	Debug_If_Condition_Message(Hull.IsNull(), "Invalid Data");

	Handle(Geom_BSplineSurface) Pair = new Geom_BSplineSurface
	(
		Hull->Poles(),
		*Hull->Weights(),
		Hull->UKnots(),
		Hull->VKnots(),
		Hull->UMultiplicities(),
		Hull->VMultiplicities(),
		Hull->UDegree(),
		Hull->VDegree()
	);
	Pair->Mirror(A2);

	TopoDS_Shape PairShape = BRepBuilderAPI_MakeFace(Pair, 1.0E-4);
	PairShape.Reverse();

	TopoDS_Compound Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompound(Compound);

	Builder.Add(Compound, model);
	Builder.Add(Compound, PairShape);

	Leg_Model_Entity::ChangeEntity() = Compound;
}

AutLib::Leg_Model_DuctNo1::Leg_Model_DuctNo1()
{
	theParameters_ = std::make_shared<Leg_DuctNo1_Parameters>();
}

void AutLib::Leg_Model_DuctNo1::Perform()
{
	AllocateMemory();

	CalcxXSections();
	
	CreateProfiles();

	CalcxParameters();
	
	CreateSections();
	
	SetupControlNet();

	SetupPatch();

	MakeFace();
	
	Change_IsDone() = Standard_True;
}

void AutLib::Leg_Model_DuctNo1::PerformToPreview()
{
	AllocateMemory();

	CalcxXSections();

	CreateProfiles();

	CalcxParameters();

	CreateSections();

	SetupControlNet();

	SetupPatch();

	MakeFace();

	ChangePreviewEntity() = Entity();
}