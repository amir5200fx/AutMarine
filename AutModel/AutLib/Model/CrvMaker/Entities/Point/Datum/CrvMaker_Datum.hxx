#pragma once
#ifndef _CrvMaker_Datum_Header
#define _CrvMaker_Datum_Header

#include <CrvMaker_Point.hxx>

namespace AutLib
{

	class CrvMaker_Datum
		: public CrvMaker_Point
	{

		/*Private Data*/

	public:

		CrvMaker_Datum()
		{}

		CrvMaker_Datum
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: CrvMaker_Point(theIndex, theCoord)
		{}

		CrvMaker_Datum
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: CrvMaker_Point(theIndex, theName, theCoord)
		{}
	};
}

#endif // !_CrvMaker_Datum_Header
