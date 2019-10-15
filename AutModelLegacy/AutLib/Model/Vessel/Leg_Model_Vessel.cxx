#include <Leg_Model_Vessel.hxx>

#include <gp_Pln.hxx>
#include <BRepAlgoAPI_Section.hxx>

TopoDS_Shape 
AutLib::Leg_Model_Vessel::GetStation
(
	const Standard_Real theX
) const
{
	BRepAlgoAPI_Section Section(Entity(), gp_Pln(gp_Pnt(theX, 0, 0), gp_Dir(1, 0, 0)));
	return Section.Shape();
}

TopoDS_Shape 
AutLib::Leg_Model_Vessel::GetButtock
(
	const Standard_Real theY
) const
{
	BRepAlgoAPI_Section Section(Entity(), gp_Pln(gp_Pnt(0, theY, 0), gp_Dir(0, 1, 0)));
	return Section.Shape();
}

TopoDS_Shape 
AutLib::Leg_Model_Vessel::GetWater
(
	const Standard_Real theZ
) const
{
	BRepAlgoAPI_Section Section(Entity(), gp_Pln(gp_Pnt(0, 0, theZ), gp_Dir(0, 0, 1)));
	return Section.Shape();
}