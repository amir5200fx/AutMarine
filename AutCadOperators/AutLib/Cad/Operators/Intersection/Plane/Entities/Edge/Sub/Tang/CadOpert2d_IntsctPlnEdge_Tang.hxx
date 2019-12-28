#pragma once
#ifndef _CadOpert2d_IntsctPlnEdge_Tang_Header
#define _CadOpert2d_IntsctPlnEdge_Tang_Header

#include <Global_AccessMethod.hxx>
#include <CadOpert2d_IntsctPlnEdge.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpert2d_IntsctCutter_TangClamped;
	class CadOpert2d_IntsctSegment;

	class CadOpert2d_IntsctPlnEdge_Tang
		: public CadOpert2d_IntsctPlnEdge
	{

		/*Private Data*/

		std::shared_ptr<CadOpert2d_IntsctSegment> theEntity_;

		std::weak_ptr<CadOpert2d_IntsctCutter_TangClamped> thePair_;

	public:

		CadOpert2d_IntsctPlnEdge_Tang()
		{}

		CadOpert2d_IntsctPlnEdge_Tang(const Standard_Integer theIndex)
			: CadOpert2d_IntsctPlnEdge(theIndex)
		{}

		Standard_Boolean IsTangential() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<CadOpert2d_IntsctCutter_TangClamped>, Pair)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctSegment>, Entity)
	};
}

#endif // !_CadOpert2d_IntsctPlnEdge_Tang_Header
