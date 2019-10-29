#pragma once
#ifndef _Mesh_PlnCurve_Header
#define _Mesh_PlnCurve_Header

#include <Standard_Handle.hxx>
#include <Entity2d_Chain.hxx>

#include <memory>

class Geom2d_Curve;

namespace AutLib
{

	// Forward Declarations
	class Geo_ApprxCurveInfo;
	class Mesh_CurveInfo;

	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;


	template<class SizeFun, class MetricFun>
	class Mesh_PlnCurve_Base
	{

		typedef Geo_MetricPrcsr<SizeFun, MetricFun> metricMap;

	protected:

		static std::shared_ptr<Entity2d_Chain> Mesh(const Handle(Geom2d_Curve)& theCurve, const Standard_Real theU0, const Standard_Real theU1, const std::shared_ptr<metricMap>& theMap, const Mesh_CurveInfo& theInfo);

		static std::shared_ptr<Entity2d_Chain> Discrete(const Handle(Geom2d_Curve)& theCurve, const Standard_Real theU0, const Standard_Real theU1, const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo);
	};

	template<class CrvEntity, class SizeFun, class MetricFun>
	class Mesh_PlnCurve
		: public CrvEntity
		, public Mesh_PlnCurve_Base<SizeFun, MetricFun>
	{

		typedef Geo_MetricPrcsr<SizeFun, MetricFun> metricMap;

		/*Private Data*/

	public:

		typedef typename CrvEntity::geomType curveType;
		typedef typename CrvEntity::infoType info;
		typedef info infoType;

		typedef Mesh_PlnCurve_Base base;

		Mesh_PlnCurve(const CrvEntity& theCurve)
			: CrvEntity(theCurve)
		{}

		Mesh_PlnCurve
		(
			const Handle(curveType)& theCurve,
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const std::shared_ptr<info>& theInfo
		)
			: CrvEntity(theFirst, theLast, theCurve, theInfo)
		{}

		std::shared_ptr<Entity2d_Chain> Discrete
		(
			const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Chain> Chain
		(
			const std::shared_ptr<metricMap>& theMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		);


	};
}

#include <Mesh_PlnCurveI.hxx>

#endif // !_Mesh_PlnCurve_Header
