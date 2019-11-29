#pragma once
#ifndef _Mesh_DefectPatch_BadMetric_Header
#define _Mesh_DefectPatch_BadMetric_Header

#include <Mesh_DefectPatch.hxx>
#include <word.hxx>

namespace AutLib
{

	struct Mesh_DefectPatch_BadMetric_TypeName
	{

		static const word typeName;
	};

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_DefectPatch_BadMetric
		: public Mesh_DefectPatch<SurfType, SizeFun, MetricFun>
		, public Mesh_DefectPatch_BadMetric_TypeName
	{

		/*Private Data*/

	public:

		typedef Mesh_DefectPatch<SurfType, SizeFun, MetricFun>
			base;

		Mesh_DefectPatch_BadMetric(const SurfType& theSurface)
			: base(theSurface)
		{}

		const word& TypeName() const override
		{
			return typeName;
		}
	};
}

#endif // !_Mesh_DefectPatch_BadMetric_Header
