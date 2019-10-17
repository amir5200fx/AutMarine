#pragma once
#ifndef _Mesh_CurveEntity_Header
#define _Mesh_CurveEntity_Header

#include <Standard_TypeDef.hxx>
#include <Geo_CascadeTraits.hxx>
#include <Global_AccessMethod.hxx>

namespace AutLib
{

	template<class gCurveType, class SizeMapType>
	class Mesh_CurveEntity
	{

		typedef typename cascadeLib::pt_type_from_curve<gCurveType>::ptType Point;

		/*Private Data*/

		const gCurveType& theCurve_;

		const SizeMapType& theSizeMap_;

		Standard_Real theFirstParameter_;
		Standard_Real theLastParameter_;

	public:

		Mesh_CurveEntity
		(
			const gCurveType& theCurve, 
			const SizeMapType& theSizeMap,
			const Standard_Real theFirst,
			const Standard_Real theLast
		);

		Point Value(const Standard_Real x) const;


		//- static members

		static Standard_Real Integrand
		(
			const Standard_Real x, 
			const Mesh_CurveEntity& theEntity
		);

		//- Macros

		GLOBAL_ACCESS_ONLY_SINGLE(gCurveType, Curve)
			GLOBAL_ACCESS_ONLY_SINGLE(SizeMapType, SizeMap)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, FirstParameter)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, LastParameter)
	};
}

#include <Mesh_CurveEntityI.hxx>

#endif // !_Mesh_CurveEntity_Header
