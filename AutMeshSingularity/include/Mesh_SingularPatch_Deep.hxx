#pragma once
#ifndef _Mesh_SingularPatch_Deep_Header
#define _Mesh_SingularPatch_Deep_Header

#include <Mesh_SingularPatch.hxx>

namespace AutLib
{

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_SingularPatch_Deep
		: public Mesh_SingularPatch<SurfType, SizeFun, MetricFun>
	{

		typedef Mesh_SingularPatch<SurfType, SizeFun, MetricFun>
			base;

		/*Private Data*/

	public:

		typedef typename base::planeType planeType;

		Mesh_SingularPatch_Deep
		(
			const SurfType& theSurface,
			const std::shared_ptr<Mesh_SingularPatch<planeType>>& theType
		)
			: base(theSurface, theType)
		{}
	};
}

#endif // !_Mesh_SingularPatch_Deep_Header
