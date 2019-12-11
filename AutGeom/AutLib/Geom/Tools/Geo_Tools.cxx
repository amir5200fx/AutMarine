#include <Geo_Tools.hxx>

#include <Pnt3d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Triangulation.hxx>

#include <Geom_Surface.hxx>

gp_Pnt
AutLib::Geo_Tools::CoordOnSurface
(
	const Pnt2d& theCoord,
	const Geom_Surface& theSurface
)
{
	auto pt = theSurface.Value(theCoord.X(), theCoord.Y());
	return std::move(pt);
}

Standard_Real 
AutLib::Geo_Tools::CalcSegmentLengthOnSurface
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1, 
	const Geom_Surface& theSurface
)
{
	auto p0 = CoordOnSurface(theP0, theSurface);
	auto p1 = CoordOnSurface(theP1, theSurface);

	return p0.Distance(p1);
}

Standard_Real 
AutLib::Geo_Tools::CalcPolyLengthOnSurface
(
	const Entity2d_Polygon& thePoly,
	const Geom_Surface& theSurface
)
{
	const auto& pts = thePoly.Points();
	if (pts.size() < 1)
	{
		return 0;
	}

	Standard_Real length = 0;
	forThose(Index, 1, pts.size() - 1)
	{
		length += 
			CalcSegmentLengthOnSurface(pts[Index - 1], pts[Index], theSurface);
	}
	return length;
}

std::shared_ptr<AutLib::Entity2d_Triangulation> 
AutLib::Geo_Tools::Triangulation
(
	const Entity2d_Box & theBox
)
{
	auto P0 = theBox.P0();
	auto P1 = theBox.Corner(Box2d_PickAlgorithm_SE);
	auto P2 = theBox.P1();
	auto P3 = theBox.Corner(Box2d_PickAlgorithm_NW);

	auto Pm = theBox.CalcCentre();

	auto triangulation = std::make_shared<Entity2d_Triangulation>();
	auto& pts = triangulation->Points();

	pts.reserve(5);
	pts.push_back(std::move(P0));
	pts.push_back(std::move(P1));
	pts.push_back(std::move(P2));
	pts.push_back(std::move(P3));
	pts.push_back(std::move(Pm));

	auto& triangles = triangulation->Connectivity();
	triangles.reserve(4);

	connectivity::triple t0;
	t0.Value(0) = 1;
	t0.Value(1) = 2;
	t0.Value(2) = 5;

	connectivity::triple t1;
	t1.Value(0) = 2;
	t1.Value(1) = 3;
	t1.Value(2) = 5;

	connectivity::triple t2;
	t2.Value(0) = 3;
	t2.Value(1) = 4;
	t2.Value(2) = 5;

	connectivity::triple t3;
	t3.Value(0) = 4;
	t3.Value(1) = 1;
	t3.Value(2) = 5;

	triangles.push_back(std::move(t0));
	triangles.push_back(std::move(t1));
	triangles.push_back(std::move(t2));
	triangles.push_back(std::move(t3));

	return std::move(triangulation);
}