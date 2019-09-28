#pragma once
#ifndef _CrvMaker_Entity_Header
#define _CrvMaker_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

namespace AutLib
{

	class CrvMaker_Entity
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

	protected:

		CrvMaker_Entity()
		{}

		CrvMaker_Entity
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
			, Global_Named("CrvMaker_Entity")
		{}

		CrvMaker_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~CrvMaker_Entity()
		{}
	};
}

#endif // !_CrvMaker_Entity_Header
