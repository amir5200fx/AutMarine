#pragma once
#ifndef _Mesh_DefectPatch_Wire_Header
#define _Mesh_DefectPatch_Wire_Header

#include <Mesh_DefectPatch.hxx>

namespace AutLib
{

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_DefectPatch_Wire
		: public Mesh_DefectPatch<SurfType, SizeFun, MetricFun>
	{

		/*Private Data*/

	protected:

		Mesh_DefectPatch_Wire(const SurfType& theSurface)
			: Mesh_DefectPatch<SurfType, SizeFun, MetricFun>(theSurface)
		{}

	public:

		typedef Mesh_DefectPatch<SurfType, SizeFun, MetricFun>
			base;

	};
}

#endif // !_Mesh_DefectPatch_Wire_Header
