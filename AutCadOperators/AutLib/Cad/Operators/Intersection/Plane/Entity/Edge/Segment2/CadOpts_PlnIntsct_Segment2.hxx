#pragma once
#ifndef _CadOpts_PlnIntsct_Segment2_Header
#define _CadOpts_PlnIntsct_Segment2_Header

#include <CadOpts_PlnIntsct_Edge.hxx>
#include <Global_AccessMethod.hxx>

namespace AutLib
{

	class CadOpts_PlnIntsct_Segment2
		: public CadOpts_PlnIntsct_Edge
	{

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge_;

	public:

		CadOpts_PlnIntsct_Segment2()
		{}

		CadOpts_PlnIntsct_Segment2
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: CadOpts_PlnIntsct_Edge(theIndex, theName)
		{}

		//- Macros
		GLOBAL_ACCESS_ONLY_SINGLE(std::shared_ptr<Pln_Edge>, Edge)
	};
}

#endif // !_CadOpts_PlnIntsct_Segment2_Header
