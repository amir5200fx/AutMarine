#pragma once
#ifndef _Mesh2d_PlnRegionAnIso_Header
#define _Mesh2d_PlnRegionAnIso_Header

#include <Mesh_PlnRegion.hxx>
#include <Mesh2d_PlnWireAnIso.hxx>

namespace AutLib
{
	typedef Mesh_PlnRegion<Mesh2d_PlnWireAnIso>
		Mesh2d_PlnRegionAnIso;
}

#endif // !_Mesh2d_PlnRegionAnIso_Header

