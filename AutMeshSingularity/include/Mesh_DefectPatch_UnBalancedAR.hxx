#pragma once
#ifndef _Mesh_DefectPatch_UnBalancedAR_Header
#define _Mesh_DefectPatch_UnBalancedAR_Header

#include <Mesh_DefectPatch.hxx>
#include <word.hxx>

namespace AutLib
{

	struct Mesh_DefectPatch_UnBalancedAR_TypeName
	{

		static const word typeName;
	};

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_DefectPatch_UnBalancedAR
		: public Mesh_DefectPatch<SurfType, SizeFun, MetricFun>
		, public Mesh_DefectPatch_UnBalancedAR_TypeName
	{

		/*Private Data*/

	public:

		typedef Mesh_DefectPatch<SurfType, SizeFun, MetricFun>
			base;

		Mesh_DefectPatch_UnBalancedAR(const SurfType& theSurface)
			: base(theSurface)
		{}

		const word& TypeName() const override
		{
			return typeName;
		}
	};
}

#endif // !_Mesh_DefectPatch_UnBalancedAR_Header
