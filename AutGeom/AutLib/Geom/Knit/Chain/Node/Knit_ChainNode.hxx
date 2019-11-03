#pragma once
#ifndef _Knit_ChainNode_Header
#define _Knit_ChainNode_Header

#include <Global_Indexed.hxx>
#include <Global_AccessMethod.hxx>
#include <Knit_ChainNode_Type.hxx>

#include <memory>

namespace AutLib
{

	template<template<class> class NodeType, class NodeTraits>
	class Knit_ChainNode
		: public NodeType<NodeTraits>
	{

		/*Private Data*/

		Knit_ChainNode_Type theType_;

	public:

		typedef NodeType<NodeTraits> base;
		typedef typename base::ptType Point;

		Knit_ChainNode(const Standard_Integer theIndex, const Point& theCoord)
			: NodeType<NodeTraits>(theIndex, theCoord)
		{}

		Knit_ChainNode(const NodeType<NodeTraits>& theNode)
			: NodeType<NodeTraits>(theNode)
		{}

		// Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Knit_ChainNode_Type, Type)
	};
}

#endif // !_Knit_ChainNode_Header
