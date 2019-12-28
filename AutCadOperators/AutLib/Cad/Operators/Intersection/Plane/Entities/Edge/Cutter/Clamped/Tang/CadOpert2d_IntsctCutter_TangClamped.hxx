#pragma once
#ifndef _CadOpert2d_IntsctCutter_TangClamped_Header
#define _CadOpert2d_IntsctCutter_TangClamped_Header

#include <Global_AccessMethod.hxx>
#include <CadOpert2d_IntsctCutter_Clamped.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpert2d_IntsctPlnEdge_Tang;
	class CadOpert2d_IntsctSegment;

	class CadOpert2d_IntsctCutter_TangClamped
		: public CadOpert2d_IntsctCutter_Clamped
	{

		/*private Data*/

		std::shared_ptr<CadOpert2d_IntsctSegment> theEntity_;

		std::weak_ptr<CadOpert2d_IntsctPlnEdge_Tang> thePair_;

	public:

		CadOpert2d_IntsctCutter_TangClamped()
		{}

		CadOpert2d_IntsctCutter_TangClamped(const Standard_Integer theIndex)
			: CadOpert2d_IntsctCutter_Clamped(theIndex)
		{}

		Standard_Boolean IsTangential() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<CadOpert2d_IntsctPlnEdge_Tang>, Pair)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctSegment>, Entity)
	};
}

#endif // !_CadOpert2d_IntsctCutter_TangClamped_Header
