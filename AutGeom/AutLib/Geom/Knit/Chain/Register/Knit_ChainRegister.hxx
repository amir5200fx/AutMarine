#pragma once
#ifndef _Knit_ChainRegister_Header
#define _Knit_ChainRegister_Header

#include <RegisterEntityM_Avl.hxx>

namespace AutLib
{
	RegisterEntity_Avl(Knit_ChainNode, NodeType);
	RegisterEntity_Avl(Knit_ChainEdge, EdgeType);
}

#endif // !_Knit_ChainRegister_Header

