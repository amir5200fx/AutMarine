#pragma once
#ifndef _Mesh_SingularPatch_Regular_Header
#define _Mesh_SingularPatch_Regular_Header

#include <Mesh_SingularPatch.hxx>

namespace AutLib
{

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_SingularPatch_Regular
		: public Mesh_SingularPatch<SurfType, SizeFun, MetricFun>
	{

		typedef Mesh_SingularPatch<SurfType, SizeFun, MetricFun>
			base;

		/*Private Data*/

	public:
		
		typedef typename base::planeType planeType;

		Mesh_SingularPatch_Regular
		(
			const SurfType& theSurface,
			const std::shared_ptr<Mesh_SingularDetection<planeType>>& theType
		)
			: base(theSurface, theType)
		{}
	};
}

#endif // !_Mesh_SingularPatch_Regular_Header
