#pragma once
#ifndef _CadOpert2d_Split_Traits_Header
#define _CadOpert2d_Split_Traits_Header

#include <Knit_ItemNode.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Vertex;
	class CadOpert2d_IntsctVertx;
	class CadOpert2d_IntsctCmpEdge;

	struct CadOpert2d_Split_Traits
	{

		typedef Knit_ItemNode<Pln_Vertex> nodeType;
		typedef Knit_ItemNode<CadOpert2d_IntsctVertx> knotType;
		typedef CadOpert2d_IntsctCmpEdge edgeType;
	};
}

#endif // !_CadOpert2d_Split_Traits_Header
