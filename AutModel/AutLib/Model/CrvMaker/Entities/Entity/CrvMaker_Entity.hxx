#pragma once
#ifndef _CrvMaker_Entity_Header
#define _CrvMaker_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace AutLib
{

	class CrvMaker_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<CrvMaker_Entity>
	{

		/*private Data*/

	protected:

		CrvMaker_Entity()
		{}

		CrvMaker_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
			, Global_Named("CrvMaker_Entity")
		{}

		CrvMaker_Entity(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~CrvMaker_Entity()
		{}


	};
}

#endif // !_CrvMaker_Entity_Header
