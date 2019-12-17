#include <CadCascade_Sphere.hxx>

#include <BRepPrimAPI_MakeSphere.hxx>

AutLib::CadCascade_Sphere::CadCascade_Sphere
(
	const Pnt3d& theCentre,
	const Standard_Real theRadius
)
{
	ChangeMaker() = 
		std::make_shared<BRepPrimAPI_MakeSphere>(theCentre, theRadius);

	ChangeShape() = Maker()->Shape();
}

AutLib::CadCascade_Sphere::CadCascade_Sphere
(
	const gp_Ax2& Axis, 
	const Standard_Real theRadius
)
{
	ChangeMaker() = 
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius);

	ChangeShape() = Maker()->Shape();
}

AutLib::CadCascade_Sphere::CadCascade_Sphere
(
	const gp_Ax2& Axis, 
	const Standard_Real theRadius,
	const Standard_Real angle1
)
{
	ChangeMaker() = 
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius, angle1);

	ChangeShape() = Maker()->Shape();
}

AutLib::CadCascade_Sphere::CadCascade_Sphere
(
	const gp_Ax2& Axis,
	const Standard_Real theRadius,
	const Standard_Real angle1,
	const Standard_Real angle2
)
{
	ChangeMaker() = 
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius, angle1, angle2);

	ChangeShape() = Maker()->Shape();
}

AutLib::CadCascade_Sphere::CadCascade_Sphere
(
	const gp_Ax2& Axis, 
	const Standard_Real theRadius, 
	const Standard_Real angle1,
	const Standard_Real angle2,
	const Standard_Real angle3
)
{
	ChangeMaker() =
		std::make_shared<BRepPrimAPI_MakeSphere>(Axis, theRadius, angle1, angle2, angle3);

	ChangeShape() = Maker()->Shape();
}