#pragma once

namespace AutLib
{

	template<class CurveType, class MetricPrcsrType>
	typename Geo_CurveIntegrand<CurveType, MetricPrcsrType>::Point 
		Geo_CurveIntegrand<CurveType, MetricPrcsrType>::CalcPoint
		(
			const Standard_Real x, 
			Vector & theVec
		) const
	{
		const auto& curve = Curve();

		Point pt;
		curve.D1(p, pt, theVec);

		return std::move(pt);
	}
}

namespace AutLib
{

	namespace GeoLib
	{

		template<class CurveType, class MetricPrcsrType, bool UnitLength = false>
		struct CurveIntegrand
		{
			static Standard_Real _
			(
				const Standard_Real x,
				const Geo_CurveIntegrand<CurveType, MetricPrcsrType>& theIntegrand
			)
			{
				typename Geo_CurveIntegrand<CurveType, MetricPrcsrType>::Vector vect;
				auto pt = theIntegrand.CalcPoint(x, vect);

				return theIntegrand.Processor().Integrand(pt, vect);
			}
		};

		template<class CurveType, class MetricPrcsrType>
		struct CurveIntegrand<CurveType, MetricPrcsrType, true>
		{
			static Standard_Real _
			(
				const Standard_Real x,
				const Geo_CurveIntegrand<CurveType, MetricPrcsrType>& theIntegrand
			)
			{
				typename Geo_CurveIntegrand<CurveType, MetricPrcsrType>::Vector vect;
				auto pt = theIntegrand.CalcPoint(x, vect);

				return theIntegrand.Processor().IntegrandPerSize(pt, vect);
			}
		};
	}
}