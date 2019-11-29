#pragma once
#ifndef _Mesh_DefectPatch_OrderWire_Header
#define _Mesh_DefectPatch_OrderWire_Header

#include <Mesh_DefectPatch_Wire.hxx>

namespace AutLib
{

	struct Mesh_DefectPatch_OrderWire_TypeName
	{

		static const word typeName;
	};

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_DefectPatch_OrderWire
		: public Mesh_DefectPatch_Wire<SurfType, SizeFun, MetricFun>
		, public Mesh_DefectPatch_OrderWire_TypeName
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::vector<std::shared_ptr<wireType>> theWires_;

	public:

		typedef Mesh_DefectPatch_Wire<SurfType, SizeFun, MetricFun>
			base;

		Mesh_DefectPatch_OrderWire
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
				std::vector<std::shared_ptr<wireType>>& theWires
			);

		static Standard_Boolean Check(const wireType& theWire);
	};
}

#include <Mesh_DefectPatch_OrderWireI.hxx>

#endif // !_Mesh_DefectPatch_OrderWire_Header
