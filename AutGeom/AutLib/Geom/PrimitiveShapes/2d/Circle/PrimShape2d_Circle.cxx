#include <PrimShape2d_Circle.hxx>

#include <error.hxx>
#include <OSstream.hxx>

void AutLib::PrimShape2d_Circle::Make()
{
	if (theNbPoints_ < 3)
	{
		FatalErrorIn("void Make()")
			<< "Invalid Nb. of points to create a circle" << endl
			<< abort(FatalError);
	}

	auto dt = (2 * PI) / (Standard_Real)theNbPoints_;

	auto& pts = Points();
	pts.reserve(theNbPoints_ + 1);

	forThose(Index, 0, theNbPoints_ - 1)
	{
		auto t = Index * dt;
		auto x = theRadius_ * cos(t);
		auto y = theRadius_ * sin(t);

		pts.push_back(Pnt2d(x, y));
	}
	pts.push_back(theCentre_);

	auto& Indices = Connectivity();
	Indices.reserve(theNbPoints_);
	forThose(Index, 0, theNbPoints_ - 2)
	{
		connectivity::triple t;
		t.Value(0) = Index + 1;
		t.Value(1) = Index + 2;
		t.Value(2) = theNbPoints_ + 1;

		Indices.push_back(std::move(t));
	}

	connectivity::triple t;
	t.Value(0) = theNbPoints_;
	t.Value(1) = 1;
	t.Value(2) = theNbPoints_ + 1;

	Indices.push_back(std::move(t));
}

void AutLib::PrimShape2d_Circle::Transform(const gp_Trsf2d & theTrasf)
{
	theCentre_.Transform(theTrasf);
	Geo2d_PrimShape::Transform(theTrasf);
}