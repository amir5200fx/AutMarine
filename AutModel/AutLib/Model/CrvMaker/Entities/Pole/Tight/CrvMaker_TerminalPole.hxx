#pragma once
#ifndef _CrvMaker_TerminalPole_Header
#define _CrvMaker_TerminalPole_Header

#include <CrvMaker_TightPole.hxx>

namespace AutLib
{


	class CrvMaker_TerminalPole
		: public CrvMaker_TightPole
	{

		/*Private Data*/

	public:

		CrvMaker_TerminalPole()
		{}

		CrvMaker_TerminalPole
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: CrvMaker_TightPole(theIndex, theCoord)
		{}

		CrvMaker_TerminalPole
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: CrvMaker_TightPole(theIndex, theName, theCoord)
		{}


		//- override functions

		Standard_Boolean IsTerminal() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_CrvMaker_TerminalPole_Header
