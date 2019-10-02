#pragma once
#ifndef _CrvMakerFrame_Corner_Header
#define _CrvMakerFrame_Corner_Header

#include <CrvMaker_Frame.hxx>

namespace AutLib
{

	template<class NodeTraits>
	class CrvMakerFrame_Corner
		: public CrvMaker_Frame<NodeTraits>
	{

		typedef CrvMaker_Node<NodeTraits> node;

		/*Private Data*/

		std::shared_ptr<node> theNode0_;
		std::shared_ptr<node> theNode1_;
		std::shared_ptr<node> theNode2_;

	protected:

		CrvMakerFrame_Corner()
		{}

		CrvMakerFrame_Corner(const Standard_Integer theIndex)
			: CrvMaker_Frame<NodeTraits>(theIndex)
		{}

		CrvMakerFrame_Corner
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: CrvMaker_Frame<NodeTraits>(theIndex, theName)
		{}

	public:

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

		const std::shared_ptr<node>& Node2() const
		{
			return theNode2_;
		}

		std::shared_ptr<node>& Node2()
		{
			return theNode2_;
		}

		//- override functions and operators

		Standard_Boolean IsClosed() const override
		{
			return Standard_False;
		}

		Standard_Integer NbNodes() const override
		{
			return 3;
		}

		const std::shared_ptr<CrvMaker_Node<NodeTraits>>& 
			Node
			(
				const Standard_Integer theIndex
			) const override
		{
			return (&theNode0_)[theIndex];
		}
	};
}

#endif // !_CrvMakerFrame_Corner_Header
