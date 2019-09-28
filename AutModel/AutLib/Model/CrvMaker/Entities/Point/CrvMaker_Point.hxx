#pragma once
#ifndef _CrvMaker_Point_Header
#define _CrvMaker_Point_Header

#include <CrvMaker_Entity.hxx>
#include <Pnt2d.hxx>

namespace AutLib
{

	class CrvMaker_Point
		: public CrvMaker_Entity
	{

		/*Private Data*/

		Pnt2d theCoord_;

	protected:

		CrvMaker_Point()
		{}

		CrvMaker_Point
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: CrvMaker_Entity(theIndex)
			, theCoord_(theCoord)
		{}

		CrvMaker_Point
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: CrvMaker_Entity(theIndex, theName)
			, theCoord_(theCoord)
		{}

	public:

		const Pnt2d& Coord() const
		{
			return theCoord_;
		}

		Pnt2d& Coord()
		{
			return theCoord_;
		}

		void SetCoord(const Pnt2d& theCoord)
		{
			theCoord_ = theCoord;
		}
	};
}

#endif // !_CrvMaker_Point_Header
