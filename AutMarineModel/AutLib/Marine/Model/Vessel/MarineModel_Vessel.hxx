#pragma once
#ifndef _MarineModel_Vessel_Header
#define _MarineModel_Vessel_Header

#include <Marine_Model.hxx>

namespace AutLib
{

	class MarineModel_Vessel
		: public Marine_Model
	{

		/*Private Data*/

	protected:

		MarineModel_Vessel()
		{}

		MarineModel_Vessel
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Marine_Model(theIndex, theName)
		{}

	public:


	};
}

#endif // !_MarineModel_Vessel_Header
