#pragma once
#ifndef _CrvMaker_Datum_Header
#define _CrvMaker_Datum_Header

#include <CrvMaker_Pole.hxx>
#include <Pnt2d.hxx>

namespace AutLib
{

	class CrvMaker_Datum
		: public CrvMaker_Pole
	{

		/*Private Data*/

		Pnt2d theCoord_;

	public:

		CrvMaker_Datum()
		{}

		CrvMaker_Datum(const Standard_Integer theIndex)
			: CrvMaker_Pole(theIndex)
		{}

		CrvMaker_Datum
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: CrvMaker_Pole(theIndex)
			, theCoord_(theCoord)
		{}

		CrvMaker_Datum
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: CrvMaker_Pole(theIndex, theName)
		{}

		CrvMaker_Datum
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: CrvMaker_Pole(theIndex, theName)
			, theCoord_(theCoord)
		{}

		const Pnt2d& Coord() const
		{
			return theCoord_;
		}

		void SetCoord(const Pnt2d& theCoord)
		{
			theCoord_ = theCoord;
		}

		//- override functions and operators

		Standard_Real xValue() const override
		{
			return theCoord_.X();
		}

		Standard_Real yValue() const override
		{
			return theCoord_.Y();
		}

	};
}

#endif // !_CrvMaker_Datum_Header
