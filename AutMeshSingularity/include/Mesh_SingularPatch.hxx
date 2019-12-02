#pragma once
#ifndef _Mesh_SingularPatch_Header
#define _Mesh_SingularPatch_Header

#include <Mesh_ImpPatch.hxx>
#include <Mesh_SingularTraits.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	template<class SurfPln>
	class Mesh_SingularDetection;

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_SingularPatch
		: public Mesh_ImpPatch<SurfType, SizeFun, MetricFun>
	{

	public:

		typedef typename singularLib::mesh_surface_plane<SurfType>::type
			planeType;

	private:

		/*Private Data*/

		std::shared_ptr<Mesh_SingularDetection<planeType>> theType_;

	protected:

		Mesh_SingularPatch
		(
			const SurfType& theSurface,
			const std::shared_ptr<Mesh_SingularDetection<planeType>>& theType
		)
			: Mesh_ImpPatch<SurfType, SizeFun, MetricFun>(theSurface)
			, theType_(theType)
		{}

	public:

		typedef Mesh_ImpPatch<SurfType, SizeFun, MetricFun>
			base;

		const std::shared_ptr<Mesh_SingularDetection<planeType>>& Type() const
		{
			return theType_;
		}
	};
}

#endif // !_Mesh_SingularPatch_Header
