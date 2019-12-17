#include <CadCascade_Box.hxx>

#include <BRepPrimAPI_MakeBox.hxx>

AutLib::CadCascade_Box::CadCascade_Box
(
	const Pnt3d& theP0, 
	const Pnt3d& theP1
)
{
	ChangeMaker() = 
		std::make_shared<BRepPrimAPI_MakeBox>(theP0, theP1);

	ChangeShape() = Maker()->Shape();
}

AutLib::CadCascade_Box::CadCascade_Box
(
	const Pnt3d& theP0, 
	const Standard_Real dx, 
	const Standard_Real dy, 
	const Standard_Real dz
)
{
	ChangeMaker() = 
		std::make_shared<BRepPrimAPI_MakeBox>(theP0, dx, dy, dz);

	ChangeShape() = Maker()->Shape();
}

AutLib::CadCascade_Box::CadCascade_Box
(
	const gp_Ax2& Axes,
	const Standard_Real dx,
	const Standard_Real dy,
	const Standard_Real dz
)
{
	ChangeMaker() = 
		std::make_shared<BRepPrimAPI_MakeBox>(Axes, dx, dy, dz);

	ChangeShape() = Maker()->Shape();
}