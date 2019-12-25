#pragma once
#ifndef _Knit_Item_Header
#define _Knit_Item_Header

#include <Global_Done.hxx>
#include <Knit_ChainNode.hxx>
#include <Knit_ChainRegister.hxx>
#include <Entity_Polygon.hxx>
#include <Entity_StaticData.hxx>
#include <Entity_Connectivity.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	template<class KnitTraits>
	class Knit_Item
		: public Global_Done
		, public RegisterKnit_ChainNode<typename KnitTraits::nodeType>
		, public RegisterKnit_ChainEdge<typename KnitTraits::edgeType>
	{

	public:

		typedef RegisterKnit_ChainNode<typename KnitTraits::nodeType> nodeRegistery;
		typedef RegisterKnit_ChainEdge<typename KnitTraits::edgeType> edgeRegistery;

		typedef typename KnitTraits::nodeType nodeType;
		typedef typename KnitTraits::edgeType edgeType;
		typedef typename nodeType::ptType ptType;
		typedef ptType Point;

		typedef std::vector<std::shared_ptr<edgeType>> itemChain;
		typedef std::vector<std::shared_ptr<itemChain>> itemList;

	private:

		/*Private Data*/

		itemList theItems_;

		// private functions

		std::shared_ptr<nodeType> Next(const std::shared_ptr<nodeType>& theNode);

		std::shared_ptr<nodeType> FindStart(const Knit_ChainNode_Type type) const;

		std::shared_ptr<itemChain> GetChain(const std::shared_ptr<nodeType>& theStart);

		void SetTypes();

	public:

		Knit_Item()
		{}

		Standard_Integer NbChains() const
		{
			return (Standard_Integer)theItems_.size();
		}

		const std::shared_ptr<itemChain>& Chain(const Standard_Integer theIndex) const
		{
			return theItems_[theIndex];
		}

		void Perform();

		void Import(const std::vector<std::shared_ptr<edgeType>>& theEdges);

		static std::vector<std::shared_ptr<nodeType>> GetNodes(const std::vector<std::shared_ptr<edgeType>>& theEdges);

	};
}

#include <Knit_ItemI.hxx>

#endif // !_Knit_Item_Header
