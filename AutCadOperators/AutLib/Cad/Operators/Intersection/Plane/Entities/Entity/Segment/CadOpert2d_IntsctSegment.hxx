#pragma once
#ifndef _CadOpert2d_IntsctSegment_Header
#define _CadOpert2d_IntsctSegment_Header

#include <CadOpert2d_IntsctEntity.hxx>
#include <Pnt2d.hxx>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

namespace AutLib
{

	class CadOpert2d_IntsctSegment
		: public CadOpert2d_IntsctEntity
	{

		/*Private Data*/

		Pnt2d theCoord0_;
		Pnt2d theCoord1_;

		Standard_Real theParameter0_;
		Standard_Real theParameter1_;

		Handle(Geom2d_Curve) theSegment_;

	public:

		CadOpert2d_IntsctSegment()
		{}

		CadOpert2d_IntsctSegment
		(
			const std::shared_ptr<Pln_Edge>& theEdge,
			const Pnt2d& theCoord0,
			const Pnt2d& theCoord1,
			const Standard_Real theP0,
			const Standard_Real theP1,
			const Handle(Geom2d_Curve)& theCurve
		)
			: CadOpert2d_IntsctEntity(theEdge)
			, theCoord0_(theCoord0)
			, theCoord1_(theCoord1)
			, theParameter0_(theP0)
			, theParameter1_(theP1)
			, theSegment_(theCurve)
		{}

		Standard_Boolean IsSegment() const override
		{
			return Standard_True;
		}

		Standard_Real MidParameter() const override
		{
			return MEAN(Parameter0(), Parameter1());
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(Pnt2d, Coord0)
			GLOBAL_ACCESS_SINGLE(Pnt2d, Coord1)

			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter0)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter1)

			GLOBAL_ACCESS_SINGLE(Handle(Geom2d_Curve), Segment)
	};
}

#endif // !_CadOpert2d_IntsctSegment_Header
