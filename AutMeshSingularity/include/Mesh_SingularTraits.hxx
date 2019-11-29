#pragma once
#ifndef _Mesh_SingularTraits_Header
#define _Mesh_SingularTraits_Header

namespace AutLib
{

	// Forward Declarations
	class Mesh2d_gPlnRegionSurface;
	class Mesh2d_tPlnRegionSurface;

	class GModel_Surface;
	class TModel_Surface;

	namespace singularLib
	{

		template<class SurfType> struct mesh_surface_plane {};

		template<> struct mesh_surface_plane<GModel_Surface> { typedef Mesh2d_gPlnRegionSurface type; };
		template<> struct mesh_surface_plane<TModel_Surface> { typedef Mesh2d_tPlnRegionSurface type; };
	}
}

#endif // !_Mesh_SingularTraits_Header
