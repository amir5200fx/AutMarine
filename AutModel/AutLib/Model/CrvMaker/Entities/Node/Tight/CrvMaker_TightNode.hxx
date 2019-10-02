#pragma once
#ifndef _CrvMaker_TightNode_Header
#define _CrvMaker_TightNode_Header

#include <CrvMaker_Node.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	template<class NodeTraits>
	class CrvMaker_Segment;


	template<class NodeTraits>
	class CrvMaker_TightNode
		: public CrvMaker_Node<NodeTraits>
	{

		typedef CrvMaker_Segment<NodeTraits> segment;

		/*Private Data*/

		std::weak_ptr<segment> theSegment0_;
		std::weak_ptr<segment> theSegment1_;

	public:

		typedef CrvMaker_Node<NodeTraits> base;

		CrvMaker_TightNode()
		{}

		CrvMaker_TightNode(const Standard_Integer theIndex)
			: base(theIndex)
		{}

		CrvMaker_TightNode
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: base(theIndex, theName)
		{}

		const std::weak_ptr<segment>& Segment0() const
		{
			return theSegment0_;
		}

		std::weak_ptr<segment>& Segment0()
		{
			return theSegment0_;
		}

		const std::weak_ptr<segment>& Segment1() const
		{
			return theSegment1_;
		}

		std::weak_ptr<segment>& Segment1()
		{
			return theSegment1_;
		}

		//- override functions ad operators

		Standard_Integer NbSegments() const override
		{
			return 2;
		}

		const std::weak_ptr<segment>& Segment(const Standard_Integer theIndex) const override
		{
			if (NOT INSIDE(theIndex, 0, NbSegments() - 1))
			{
				FatalErrorIn("const std::weak_ptr<segment>& Segment(const Standard_Integer theIndex) const override")
					<< "Invalid Index: " << theIndex << std::endl
					<< abort(FatalError);
			}
			return (&theSegment0_)[theIndex];
		}
	};
}

#endif // !_CrvMaker_TightNode_Header
