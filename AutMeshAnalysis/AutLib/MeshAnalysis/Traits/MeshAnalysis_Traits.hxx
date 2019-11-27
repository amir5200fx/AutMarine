#pragma once
#ifndef _MeshAnalysis_Traits_Header
#define _MeshAnalysis_Traits_Header

namespace AutLib
{

	// Forward Declarations
	class GModel_Curve;
	class GModel_Surface;
	class TModel_Curve;
	class TModel_Surface;

	class Cad3d_GModel;
	class Cad3d_TModel;

	class Pln_Curve;

	class Cad2d_Plane;

	namespace meshAnalysis
	{
		template<class CurveType, class SurfType>
		struct model_type{};

		template<> struct model_type<GModel_Curve, GModel_Surface> { typedef Cad3d_GModel type; };
		template<> struct model_type<TModel_Curve, TModel_Surface> { typedef Cad3d_TModel type; };

		template<> struct model_type<Pln_Curve, void> { typedef Cad2d_Plane type; };
	}

	
}

#endif // !_MeshAnalysis_Traits_Header
