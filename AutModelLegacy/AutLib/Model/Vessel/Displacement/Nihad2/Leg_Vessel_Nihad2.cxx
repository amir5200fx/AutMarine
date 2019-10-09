#include <Leg_Vessel_Nihad2.hxx>

#include <gp_Pln.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TColGeom_Array1OfBSplineCurve.hxx>

void AutLib::Leg_Nihad2_HullPatch::AllocateMemory()
{
	const auto& dimensions = Dimensions();

	auto nbSections = dimensions.NbNetColumns();
	auto nbRows = dimensions.NbNetRows();

	Leg_Nihad2_Xparams::AllocateMemory(nbSections);

	Leg_Nihad2_Profile::AllocateMemory(nbSections);

	CtrlNet =
		std::make_shared<TColgp_Array2OfPnt>(1, nbSections, 1, nbRows);
}

void AutLib::Leg_Nihad2_HullPatch::MakeFace()
{
	Leg_Model_Entity::ChangeEntity() =
		BRepBuilderAPI_MakeFace(theHull_, 1.0E-6);

	Leg_Model_EntitySystem::System() =
		gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));
}

void AutLib::Leg_Nihad2_HullPatch::Perform()
{
	AllocateMemory();

	CalcxXSections();

	CalcxParameters();

	CreateRawSections();

	ApplyParameters();

	SetupControlNet();

	SetupPatch();

	MakeFace();

	Change_IsDone() = Standard_True;
}