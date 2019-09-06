#pragma once
#ifndef _Mesh_PlnCurve_Header
#define _Mesh_PlnCurve_Header

#include <Entity2d_Chain.hxx>
#include <Geo_ApprxCurveInfo.hxx>
#include <Mesh2d_SizeMapSurface.hxx>
#include <Mesh2d_SizeMapAnIso.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Mesh_CurveInfo.hxx>

namespace AutLib
{

	template<class CrvEntity>
	class Mesh_PlnCurve
	{

		/*Private Data*/

	public:

		typedef typename CrvEntity::geomType curveType;
		typedef typename CrvEntity::infoType infoType;

		Mesh_PlnCurve(const CrvEntity& theCurve)
			: CrvEntity(theCurve)
		{}

		Mesh_PlnCurve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(curveType)& theCurve,
			const std::shared_ptr<infoType>& theInfo
		)
			: CrvEntity(theFirst, theLast, theCurve, theInfo)
		{}



		std::shared_ptr<Entity2d_Chain> Discrete
		(
			const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapSurface>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapAnIso>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const;
	};
}

#endif // !_Mesh_PlnCurve_Header
