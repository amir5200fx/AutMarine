#pragma once
#ifndef _Mesh3d_NodeTraits_Header
#define _Mesh3d_NodeTraits_Header

#include <Mesh3d_EdgeFwd.hxx>
#include <Mesh3d_FacetFwd.hxx>
#include <Mesh3d_ElementFwd.hxx>

namespace AutLib
{

	struct Mesh3d_NodeTraits
	{

		typedef Mesh3d_Edge edgeType;
		typedef Mesh3d_Facet facetType;
		typedef Mesh3d_Element elementType;
	};
}

#endif // !_Mesh3d_NodeTraits_Header
