#pragma once
#ifndef _Mesh_DefectPatch_IntersectWire_Header
#define _Mesh_DefectPatch_IntersectWire_Header

#include <Mesh_DefectPatch_Wire.hxx>

namespace AutLib
{

	struct Mesh_DefectPatch_IntersectWire_TypeName
	{

		static const word typeName;
	};

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_DefectPatch_IntersectWire
		: public Mesh_DefectPatch_Wire<SurfType, SizeFun, MetricFun>
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::shared_ptr<wireType> theWire1_;
		std::shared_ptr<wireType> theWire2_;

	public:

		typedef Mesh_DefectPatch_Wire<SurfType, SizeFun, MetricFun> 
			base;

		Mesh_DefectPatch_IntersectWire
		(
			const SurfType& theSurface,
			const std::shared_ptr<wireType>& theWire1, 
			const std::shared_ptr<wireType>& theWire2
		)
			: base(theSurface)
			, theWire1_(theWire1)
			, theWire2_(theWire2)
		{}

		const word& TypeName() const override
		{
			return typeName;
		}

		//- Static functions and operators

		static Standard_Boolean
			Check
			(
				const SurfType& theSurface,
				std::shared_ptr<wireType>& theOuter,
				std::shared_ptr<wireType>& theInner,
				const Standard_Real theTol
			);
	};
}

#include <Mesh_DefectPatch_IntersectWireI.hxx>

#endif // !_Mesh_DefectPatch_IntersectWire_Header
