#pragma once
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class NodeType>
	Standard_Boolean Knit_ItemNode<NodeType>::IsLess
	(
		const std::shared_ptr<Knit_ItemNode>& theNode0, 
		const std::shared_ptr<Knit_ItemNode>& theNode1
	)
	{
		Debug_Null_Pointer(theNode0);
		Debug_Null_Pointer(theNode1);

		return theNode0->Index() < theNode1->Index();
	}
}