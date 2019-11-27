#include <Geo_Tools.hxx>

#include <Pnt3d.hxx>
#include <Entity2d_Polygon.hxx>

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