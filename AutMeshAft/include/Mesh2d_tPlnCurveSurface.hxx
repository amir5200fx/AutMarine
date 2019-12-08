#pragma once
#ifndef _Mesh2d_tPlnCurveSurface_Header
#define _Mesh2d_tPlnCurveSurface_Header

#include <Mesh2d_PlnCurveAnIso_Base.hxx>
#include <Aft2d_tSegmentEdgeFwd.hxx>
#include <TModel_parCurve.hxx>

namespace AutLib
{

	typedef Mesh_PlnCurve<TModel_parCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Mesh2d_tPlnCurveSurface;

	template<>
	template<>
	static std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Mesh2d_tPlnCurveSurface::TopoMesh<Aft2d_tSegmentEdge>
		(
			const std::shared_ptr<Mesh2d_tPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
			);
}

#endif // !_Mesh2d_tPlnCurveSurface_Header
