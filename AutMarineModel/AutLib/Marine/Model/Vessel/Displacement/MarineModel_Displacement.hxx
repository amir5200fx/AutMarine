#pragma once
#ifndef _MarineModel_Displacement_Header
#define _MarineModel_Displacement_Header

#include <MarineModel_Vessel.hxx>

namespace AutLib
{

	class MarineModel_Displacement
		: public MarineModel_Vessel
	{

		/*Private Data*/

	protected:

		MarineModel_Displacement()
		{}

		MarineModel_Displacement
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: MarineModel_Vessel(theIndex, theName)
		{}

	public:


	};
}

#endif // !_MarineModel_Displacement_Header
