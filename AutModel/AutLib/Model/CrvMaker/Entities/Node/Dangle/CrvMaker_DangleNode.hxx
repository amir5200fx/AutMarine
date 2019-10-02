#pragma once
#ifndef _CrvMaker_DangleNode_Header
#define _CrvMaker_DangleNode_Header

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
	class CrvMaker_DangleNode
		: public CrvMaker_Node<NodeTraits>
	{

		typedef CrvMaker_Segment<NodeTraits> segment;

		/*Private Data*/

		std::weak_ptr<segment> theSegment_;

	public:

		typedef CrvMaker_Node<NodeTraits> base;

		CrvMaker_DangleNode()
		{}

		CrvMaker_DangleNode(const Standard_Integer theIndex)
			: base(theIndex)
		{}

		CrvMaker_DangleNode
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: base(theIndex, theName)
		{}


		const std::weak_ptr<segment>& Segment() const
		{
			return theSegment_;
		}

		std::weak_ptr<segment>& Segment()
		{
			return theSegment_;
		}

		//- override functions ad operators

		Standard_Integer NbSegments() const override
		{
			return 1;
		}

		const std::weak_ptr<segment>& Segment(const Standard_Integer theIndex) const override
		{
			if (NOT INSIDE(theIndex, 0, NbSegments() - 1))
			{
				FatalErrorIn("const std::weak_ptr<segment>& Segment(const Standard_Integer theIndex) const override")
					<< "Invalid Index: " << theIndex << std::endl
					<< abort(FatalError);
			}
			return theSegment_;
		}
	};
}

#endif // !_CrvMaker_DangleNode_Header
