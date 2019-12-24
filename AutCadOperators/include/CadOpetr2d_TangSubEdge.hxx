#pragma once
#ifndef _CadOpetr2d_TangSubEdge_Header
#define _CadOpetr2d_TangSubEdge_Header

#include <CadOpetr2d_SubEdge.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpetr2d_TangCutterEdge;

	class CadOpetr2d_TangSubEdge
		: public CadOpetr2d_SubEdge
	{

		/*Private Data*/

		std::weak_ptr<CadOpetr2d_TangCutterEdge> thePair_;

	public:

		CadOpetr2d_TangSubEdge()
		{}

		CadOpetr2d_TangSubEdge
		(
			const Standard_Integer theIndex
		)
			: CadOpetr2d_SubEdge(theIndex)
		{}

		Standard_Boolean IsTangential() const override
		{
			return Standard_True;
		}

		const std::weak_ptr<CadOpetr2d_TangCutterEdge>& Pair() const
		{
			return thePair_;
		}

		void SetPair
		(
			const std::weak_ptr<CadOpetr2d_TangCutterEdge>& thePair
		)
		{
			thePair_ = thePair;
		}
	};
}

#endif // !_CadOpetr2d_TangSubEdge_Header
