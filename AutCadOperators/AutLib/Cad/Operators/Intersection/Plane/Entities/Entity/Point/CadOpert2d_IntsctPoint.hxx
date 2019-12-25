#pragma once
#ifndef _CadOpert2d_IntsctPoint_Header
#define _CadOpert2d_IntsctPoint_Header

#include <CadOpert2d_IntsctEntity.hxx>
#include <Pnt2d.hxx>

namespace AutLib
{

	class CadOpert2d_IntsctPoint
		: public CadOpert2d_IntsctEntity
	{

		/*Private Data*/

		Pnt2d theCoord_;

		Standard_Real theParameter_;

	public:

		CadOpert2d_IntsctPoint()
		{}

		CadOpert2d_IntsctPoint
		(
			const std::shared_ptr<Pln_Edge>& theParent,
			const Pnt2d& theCoord,
			const Standard_Real theParameter
		)
			: CadOpert2d_IntsctEntity(theParent)
			, theCoord_(theCoord)
			, theParameter_(theParameter)

		{}

		Standard_Boolean IsPoint() const override
		{
			return Standard_True;
		}

		Standard_Real MidParameter() const override
		{
			return theParameter_;
		}

		// macros

		GLOBAL_ACCESS_SINGLE(Pnt2d, Coord)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter)
	};
}

#endif // !_CadOpert2d_IntsctPoint_Header
