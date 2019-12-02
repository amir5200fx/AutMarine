#pragma once
#ifndef _MeshAnalysis_Model_Traits_Header
#define _MeshAnalysis_Model_Traits_Header

#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>

namespace AutLib
{

	struct MeshAnalysis_Model_Traits
	{

		typedef Geo2d_SizeFunction sizeFun;
		typedef Geo2d_MetricFunction metricFun;
	};
}

#endif // !_MeshAnalysis_Model_Traits_Header
