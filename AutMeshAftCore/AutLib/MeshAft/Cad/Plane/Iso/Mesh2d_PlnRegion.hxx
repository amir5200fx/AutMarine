#pragma once
#ifndef _Mesh2d_PlnRegion_Header
#define _Mesh2d_PlnRegion_Header

#include <Mesh_PlnRegion.hxx>
#include <Mesh2d_PlnWire.hxx>

namespace AutLib
{
	typedef Mesh_PlnRegion<Mesh2d_PlnWire>
		Mesh2d_PlnRegion;
}

#endif // !_Mesh2d_PlnRegion_header
