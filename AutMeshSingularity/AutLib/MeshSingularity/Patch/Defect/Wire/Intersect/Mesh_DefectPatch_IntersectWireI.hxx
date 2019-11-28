#pragma once
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	template<class SurfType, class SizeFun, class MetricFun>
	Standard_Boolean Mesh_DefectPatch_IntersectWire<SurfType, SizeFun, MetricFun>::Check
	(
		const SurfType & theSurface, 
		std::shared_ptr<wireType>& theWire1, 
		std::shared_ptr<wireType>& theWire2,
		const Standard_Real theTol
	)
	{
		if (NOT theSurface.HasHole())
		{
			return Standard_False;
		}

		theWire1 = theSurface.OuterWire();

		const auto& outer = theSurface.OuterWire();
		const auto& inners = *theSurface.InnerWires();

		auto oBox = outer->CalcParametricBoundingBox();

		for (const auto& x : inners)
		{
			Debug_Null_Pointer(x);
			auto iBox = x->CalcParametricBoundingBox();

			auto offset = iBox.OffSet(theTol);

			if (NOT Entity2d_Box::IsInside(offset, oBox))
			{
				theWire2 = x;
				return Standard_True;
			}
		}

		return Standard_False;
	}
}