#pragma once
#ifndef _CadOpetr2d_TangCutterEdge_Header
#define _CadOpetr2d_TangCutterEdge_Header

#include <CadOpetr2d_CutterEdge.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpetr2d_TangSubEdge;

	class CadOpetr2d_TangCutterEdge
		: public CadOpetr2d_CutterEdge
	{

		/*Private Data*/

		std::weak_ptr<CadOpetr2d_TangSubEdge> thePair_;

	public:

		CadOpetr2d_TangCutterEdge()
		{}

		CadOpetr2d_TangCutterEdge(const Standard_Integer theIndex)
			: CadOpetr2d_CutterEdge(theIndex)
		{}

		Standard_Boolean IsTangential() const override
		{
			return Standard_True;
		}

		const std::weak_ptr<CadOpetr2d_TangSubEdge>& Pair() const
		{
			return thePair_;
		}

		void SetPair(const std::weak_ptr<CadOpetr2d_TangSubEdge>& thePair)
		{
			thePair_ = thePair;
		}
	};
}

#endif // !_CadOpetr2d_TangCutterEdge_Header
