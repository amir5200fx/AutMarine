#pragma once
#ifndef _Aft_PlnBoundary_Base_Header
#define _Aft_PlnBoundary_Base_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>

namespace AutLib
{

	template<class BndEdgeType>
	class Aft_PlnBoundary_Base
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		/*Private Data*/

	protected:

		Aft_PlnBoundary_Base()
		{}

	public:


	};
}

#endif // !_Aft_PlnBoundary_Base_Header
