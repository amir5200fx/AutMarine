#include <PrimShape2d_Rectangle.hxx>

void AutLib::PrimShape2d_Rectangle::Make()
{
	auto& pts = Points();
	pts.reserve(4);

	pts.push_back(theP0_);
	pts.push_back(theP0_ + Pnt2d(theDx_, theP0_.Y()));
	pts.push_back(theP0_ + Pnt2d(theDx_, theDy_));
	pts.push_back(theP0_ + Pnt2d(theP0_.X(), theDy_));

	auto& Indices = Connectivity();
	Indices.reserve(2);

	connectivity::triple t0;
	t0.Value(0) = 1;
	t0.Value(1) = 2;
	t0.Value(2) = 3;

	connectivity::triple t1;
	t1.Value(0) = 3;
	t1.Value(1) = 4;
	t1.Value(2) = 1;

	Indices.push_back(std::move(t0));
	Indices.push_back(std::move(t1));
}

void AutLib::PrimShape2d_Rectangle::Transform(const gp_Trsf2d & theTrasf)
{
	theP0_.Transform(theTrasf);
	Geo2d_PrimShape::Transform(theTrasf);
}