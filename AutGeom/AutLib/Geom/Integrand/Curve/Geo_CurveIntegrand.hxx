#pragma once
#ifndef _Geo_CurveIntegrand_Header
#define _Geo_CurveIntegrand_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Geo_CascadeTraits.hxx>

namespace AutLib
{

	template<class CurveType, class MetricPrcsrType>
	class Geo_CurveIntegrand
	{

		/*Private Data*/

		const CurveType& theCurve_;

		const MetricPrcsrType& theProcessor_;

	public:

		typedef typename cascadeLib::pt_type_from_curve<CurveType>::ptType Point;
		typedef typename cascadeLib::vec_type_from_point<CurveType>::vcType Vector;

		Geo_CurveIntegrand
		(
			const CurveType& theCurve,
			const MetricPrcsrType& theProcessor
		)
			: theCurve_(theCurve)
			, theProcessor_(theProcessor)
		{}

		const CurveType& Curve() const
		{
			return theCurve_;
		}

		const MetricPrcsrType& Processor() const
		{
			return theProcessor_;
		}

		Point CalcPoint(const Standard_Real x, Vector& theVec) const;
	};
}

#include <Geo_CurveIntegrandI.hxx>

#endif // !_Geo_CurveIntegrand_Header
