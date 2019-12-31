#pragma once
#ifndef _Knit_ItemNode_Header
#define _Knit_ItemNode_Header

#include <Global_Indexed.hxx>
#include <Global_AccessMethod.hxx>
#include <Knit_ChainNode_Type.hxx>

#include <memory>

namespace AutLib
{

	template<class NodeType>
	class Knit_ItemNode
	{

		/*Private Data*/

		std::shared_ptr<NodeType> theNode_;

		Knit_ChainNode_Type theType_;

	public:

		typedef NodeType nodeType;
		typedef typename NodeType::ptType Point;

		Knit_ItemNode(const std::shared_ptr<NodeType>& theNode)
			: theNode_(theNode)
		{}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Knit_ItemNode>& theNode0,
			const std::shared_ptr<Knit_ItemNode>& theNode1
		);

		Standard_Integer NbEdges() const
		{
			return theNode_->NbEdges();
		}

		Standard_Integer Index() const
		{
			return theNode_->Index();
		}

		const auto& Coord() const
		{
			return theNode_->Coord();
		}

		auto RetrieveEdges() const
		{
			auto edges = theNode_->RetrieveEdges();
			return std::move(edges);
		}

		void RemoveFromEdges(const Standard_Integer theIndex)
		{
			theNode_->RemoveFromEdges(theIndex);
		}

		// Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Knit_ChainNode_Type, Type)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<NodeType>, Node)
	};
}

#include <Knit_ItemNodeI.hxx>

#endif // !_Knit_ItemNode_Header
