#pragma once
#ifndef _CrvMaker_Segment_Header
#define _CrvMaker_Segment_Header

#include <CrvMaker_Entity.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	template<class NodeTraits>
	class CrvMaker_Node;


	template<class NodeTraits>
	class CrvMaker_Segment
		: public CrvMaker_Entity
	{

		typedef CrvMaker_Node<NodeTraits> node;

		/*Private Data*/

		std::shared_ptr<node> theNode0_;
		std::shared_ptr<node> theNode1_;

	public:

		CrvMaker_Segment()
		{}

		CrvMaker_Segment
		(
			const std::shared_ptr<node>& theNode0,
			const std::shared_ptr<node>& theNode1
		)
			: theNode0_(theNode0)
			, theNode1_(theNode1)
		{}

		CrvMaker_Segment(const Standard_Integer theIndex)
			: CrvMaker_Entity(theIndex)
		{}

		CrvMaker_Segment
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<node>& theNode0,
			const std::shared_ptr<node>& theNode1
		)
			: CrvMaker_Entity(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
		{}

		CrvMaker_Segment
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::shared_ptr<node>& theNode0, 
			const std::shared_ptr<node>& theNode1
		)
			: CrvMaker_Entity(theIndex, theName)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
		{}

		const std::shared_ptr<node>& Node0() const
		{
			return theNode0_;
		}

		std::shared_ptr<node>& Node0()
		{
			return theNode0_;
		}

		const std::shared_ptr<node>& Node1() const
		{
			return theNode1_;
		}

		std::shared_ptr<node>& Node1()
		{
			return theNode1_;
		}


	};
}

#endif // !_CrvMaker_Segment_Header
