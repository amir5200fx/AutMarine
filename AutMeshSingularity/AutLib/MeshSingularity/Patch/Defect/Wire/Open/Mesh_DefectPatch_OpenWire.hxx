#pragma once
#ifndef _Mesh_DefectPatch_OpenWire_Header
#define _Mesh_DefectPatch_OpenWire_Header

#include <Mesh_DefectPatch_Wire.hxx>

#include <vector>
#include <map>

namespace AutLib
{

	struct Mesh_DefectPatch_OpenWire_TypeName
	{

		static const word typeName;
	};

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_DefectPatch_OpenWire
		: public Mesh_DefectPatch_Wire<SurfType, SizeFun, MetricFun>
		, public Mesh_DefectPatch_OpenWire_TypeName
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::vector<std::shared_ptr<wireType>> theWires_;

	public:	

		typedef Mesh_DefectPatch_Wire<SurfType, SizeFun, MetricFun>
			base;

		Mesh_DefectPatch_OpenWire
		(
			const SurfType& theSurface, 
			const std::vector<std::shared_ptr<wireType>>& theWires
		)
			: base(theSurface)
			, theWires_(theWires)
		{}

		const std::vector<std::shared_ptr<wireType>>& Wires() const
		{
			return theWires_;
		}

		const word& TypeName() const override
		{
			return typeName;
		}

		//- Static functions and operators

		static Standard_Boolean
			Check
			(
				const SurfType& theSurface,
				std::vector<std::shared_ptr<wireType>>& theWires,
				const Standard_Real theTol
			);

		static Standard_Boolean
			Check
			(
				const wireType& theWire,
				const Standard_Real theTol
			);
	};
}

#include <Mesh_DefectPatch_OpenWireI.hxx>

#endif // !_Mesh_DefectPatch_OpenWire_Header
