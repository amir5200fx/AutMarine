#pragma once
#ifndef _CrvMaker_Pole_Header
#define _CrvMaker_Pole_Header

#include <CrvMaker_Entity.hxx>

namespace AutLib
{

	class CrvMaker_Pole
		: public CrvMaker_Entity
	{

		/*Private Data*/

	protected:

		CrvMaker_Pole()
		{}

		CrvMaker_Pole
		(
			const Standard_Integer theIndex
		)
			: CrvMaker_Entity(theIndex)
		{}

		CrvMaker_Pole
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: CrvMaker_Entity(theIndex, theName)
		{}

	public:


		virtual Standard_Real xValue() const = 0;

		virtual Standard_Real yValue() const = 0;
	};
}

#endif // !_CrvMaker_Pole_Header
