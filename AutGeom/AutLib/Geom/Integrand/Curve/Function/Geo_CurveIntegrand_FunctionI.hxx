#pragma once
#include <Geo_CurveIntegrand.hxx>
namespace AutLib
{

	template<class CurveType, class MetricPrcsrType, bool UnitLength>
	Standard_Real Geo_CurveIntegrand_Function<CurveType, MetricPrcsrType, UnitLength>::Value
	(
		const Standard_Real x
	) const
	{
		return GeoLib::CurveIntegrand<CurveType, MetricPrcsrType, UnitLength>::_(x, Entity());
	}
}