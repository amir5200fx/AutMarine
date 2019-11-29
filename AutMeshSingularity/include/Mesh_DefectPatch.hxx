#pragma once
#ifndef _Mesh_DefectPatch_Header
#define _Mesh_DefectPatch_Header

#include <Mesh_ImpPatch.hxx>
#include <word.hxx>

namespace AutLib
{

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_DefectPatch
		: public Mesh_ImpPatch<SurfType, SizeFun, MetricFun>
	{

		/*Private Data*/

	protected:

		Mesh_DefectPatch(const SurfType& theSurface)
			: Mesh_ImpPatch<SurfType, SizeFun, MetricFun>(theSurface)
		{}

	public:

		typedef Mesh_ImpPatch<SurfType, SizeFun, MetricFun>
			base;

		virtual const word& TypeName() const = 0;
	};
}

#endif // !_Mesh_DefectPatch_Header
