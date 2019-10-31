#pragma once
#ifndef _Geo3d_MetricPrcsrAnIso_Header
#define _Geo3d_MetricPrcsrAnIso_Header

#include <Geo_MetricPrcsr.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Geo3d_MetricFunction.hxx>

namespace AutLib
{
	typedef Geo_MetricPrcsr<Geo3d_SizeFunction, Geo3d_MetricFunction>
		Geo3d_MetricPrcsrAnIso;
}

#endif // !_Geo3d_MetricPrcsrAnIso_Header
