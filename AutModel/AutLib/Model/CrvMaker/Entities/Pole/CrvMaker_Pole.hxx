#pragma once
#ifndef _CrvMaker_Pole_Header
#define _CrvMaker_Pole_Header

#include <CrvMaker_Point.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CrvMaker_Segment;

	class CrvMaker_Pole
		: public CrvMaker_Point
	{

		/*Private Data*/

	protected:

		CrvMaker_Pole()
		{}

		CrvMaker_Pole
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: CrvMaker_Point(theIndex, theCoord)
		{}

		CrvMaker_Pole
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: CrvMaker_Point(theIndex, theName, theCoord)
		{}

	public:

		//- virtual functions

		virtual Standard_Boolean IsDangle() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTight() const
		{
			return Standard_False;
		}

		virtual Standard_Integer NbSegments() const = 0;

		virtual const std::weak_ptr<CrvMaker_Segment>& 
			Segment
			(
				const Standard_Integer theIndex
			) const = 0;
	};
}

#endif // !_CrvMaker_Pole_Header
