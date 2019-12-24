#pragma once
#ifndef _CadOpetr2d_IntsctPoint_Header
#define _CadOpetr2d_IntsctPoint_Header

#include <CadOpetr2d_IntsctEntity.hxx>
#include <Pnt2d.hxx>

namespace AutLib
{

	class CadOpetr2d_IntsctPoint
		: public CadOpetr2d_IntsctEntity
	{

		/*Private Data*/

		Pnt2d theCoord_;

		Standard_Real theParameter_;

	public:

		CadOpetr2d_IntsctPoint()
		{}

		CadOpetr2d_IntsctPoint
		(
			const std::shared_ptr<Pln_Edge>& theParent,
			const Pnt2d& theCoord,
			const Standard_Real theParameter
		)
			: CadOpetr2d_IntsctEntity(theParent)
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

#endif // !_CadOpetr2d_IntsctPoint_Header
