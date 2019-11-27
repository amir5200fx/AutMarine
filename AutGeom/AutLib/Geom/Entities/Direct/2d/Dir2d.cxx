#include <Dir2d.hxx>

#include <Pnt2d.hxx>

const AutLib::Dir2d AutLib::Dir2d::null((Standard_Real)1., (Standard_Real)0.);

AutLib::Dir2d::Dir2d
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
)
{
	auto v = theP1 - theP0;

	*this = Dir2d(v.X(), v.Y());
}