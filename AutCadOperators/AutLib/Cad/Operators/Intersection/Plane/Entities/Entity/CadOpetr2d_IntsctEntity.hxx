#pragma once
#ifndef _CadOpetr2d_IntsctEntity_Header
#define _CadOpetr2d_IntsctEntity_Header

#include <Global_AccessMethod.hxx>
#include <Standard_TypeDef.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;

	class CadOpetr2d_IntsctEntity
	{

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge_;

		std::weak_ptr<CadOpetr2d_IntsctEntity> thePair_;

	protected:

		CadOpetr2d_IntsctEntity()
		{}

		CadOpetr2d_IntsctEntity
		(
			const std::shared_ptr<Pln_Edge>& theParent
		)
			: theEdge_(theParent)
		{}

	public:

		const std::weak_ptr<CadOpetr2d_IntsctEntity>& Pair() const
		{
			return thePair_;
		}

		void SetPair(const std::weak_ptr<CadOpetr2d_IntsctEntity>& thePair)
		{
			thePair_ = thePair;
		}

		virtual Standard_Boolean IsPoint() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSegment() const
		{
			return Standard_False;
		}

		virtual Standard_Real MidParameter() const = 0;

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<CadOpetr2d_IntsctEntity>& theE0,
			const std::shared_ptr<CadOpetr2d_IntsctEntity>& theE1
		)
		{
			return theE0->MidParameter() < theE1->MidParameter();
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Pln_Edge>, Edge)
	};
}

#endif // !_CadOpetr2d_IntsctEntity_Header
