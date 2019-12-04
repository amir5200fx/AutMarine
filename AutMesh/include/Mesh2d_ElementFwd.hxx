#pragma once
#ifndef _Mesh2d_ElementFwd_Header
#define _Mesh2d_ElementFwd_Header

#include <Mesh_ElementType.hxx>

namespace AutLib
{

	// Forward Declarations

	struct Mesh2d_ElementTraits;

	template<class ElementTraits, Mesh_ElementType ElmType = Mesh_ElementType_Tetrahedron>
	class Mesh_Element;

	typedef Mesh_Element<Mesh2d_ElementTraits, Mesh_ElementType_Triangle2D>
		Mesh2d_Element;
}

#endif // !_Mesh2d_ElementFwd_Header
