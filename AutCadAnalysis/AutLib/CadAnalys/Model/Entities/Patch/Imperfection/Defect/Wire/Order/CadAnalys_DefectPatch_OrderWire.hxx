#pragma once
#ifndef _CadAnalys_DefectPatch_OrderWire_Header
#define _CadAnalys_DefectPatch_OrderWire_Header

#include <CadAnalys_DefectPatch_Wire.hxx>

#include <vector>

namespace AutLib
{

	template<class SurfType>
	class CadAnalys_DefectPatch_OrderWire
		: public CadAnalys_DefectPatch_Wire<SurfType>
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::vector<std::shared_ptr<wireType>> theWires_;

	public:

		typedef CadAnalys_DefectPatch_Wire<SurfType>
			base;

		CadAnalys_DefectPatch_OrderWire
		(
			const std::shared_ptr<SurfType>& theSurface,
			const std::vector<std::shared_ptr<wireType>>& theWires
		)
			: CadAnalys_DefectPatch_Wire<SurfType>(theSurface)
			, theWires_(theWires)
		{}

		const std::vector<std::shared_ptr<wireType>>& Wires() const
		{
			return theWires_;
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

#include <CadAnalys_DefectPatch_OrderWireI.hxx>

#endif // !_CadAnalys_DefectPatch_OrderWire_Header
