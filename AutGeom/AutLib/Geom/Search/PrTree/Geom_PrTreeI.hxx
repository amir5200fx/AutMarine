#pragma once
namespace AutLib
{
	inline Geo_Quadrant CalcQuadrant
	(
		const Pnt2d & theCoord,
		const Pnt2d & theCentre
	)
	{
		if (theCoord.X() <= theCentre.X())
			if (theCoord.Y() <= theCentre.Y())
				return Geo_Quadrant_SW;
			else
				return Geo_Quadrant_NW;
		else
		{
			if (theCoord.Y() <= theCentre.Y())
				return Geo_Quadrant_SE;
			else
				return Geo_Quadrant_NE;
		}
	}
}