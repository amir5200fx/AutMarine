#include <CadCascade_Cylinder.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>

AutLib::CadCascade_Cylinder::CadCascade_Cylinder
(
	const gp_Ax2& Axes, 
	const Standard_Real R, 
	const Standard_Real H
)
{
	ChangeMaker() = std::make_shared<BRepPrimAPI_MakeCylinder>(Axes, R, H);

	ChangeShape() = Maker()->Shape();
}

AutLib::CadCascade_Cylinder::CadCascade_Cylinder
(
	const gp_Ax2& Axes, 
	const Standard_Real R, 
	const Standard_Real H,
	const Standard_Real Angle
)
{
	ChangeMaker() = std::make_shared<BRepPrimAPI_MakeCylinder>(Axes, R, H, Angle);

	ChangeShape() = Maker()->Shape();
}