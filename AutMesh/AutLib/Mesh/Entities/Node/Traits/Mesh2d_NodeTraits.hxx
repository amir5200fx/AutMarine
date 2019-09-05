#pragma once
#ifndef _Mesh2d_NodeTraits_Header
#define _Mesh2d_NodeTraits_Header

#include <Mesh2d_EdgeFwd.hxx>
#include <Mesh2d_ElementFwd.hxx>

namespace AutLib
{

	struct Mesh2d_NodeTraits
	{

		typedef Mesh2d_Edge edgeType;
		typedef void facetType;
		typedef Mesh2d_Element elementType;
	};
}

#endif // !_Mesh2d_NodeTraits_Header

