#pragma once
#ifndef _CadOpert2d_IntsctCutter_OrthClamped_Header
#define _CadOpert2d_IntsctCutter_OrthClamped_Header

#include <Global_AccessMethod.hxx>
#include <CadOpert2d_IntsctCutter_Clamped.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpert2d_IntsctPoint;

	class CadOpert2d_IntsctCutter_OrthClamped
		: public CadOpert2d_IntsctCutter_Clamped
	{

		/*Private Data*/

		std::shared_ptr<CadOpert2d_IntsctPoint> theEntity0_;
		std::shared_ptr<CadOpert2d_IntsctPoint> theEntity1_;

	public:

		CadOpert2d_IntsctCutter_OrthClamped()
		{}

		CadOpert2d_IntsctCutter_OrthClamped(const Standard_Integer theIndex)
			: CadOpert2d_IntsctCutter_Clamped(theIndex)
		{}

		Standard_Boolean IsOrthogonal() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctPoint>, Entity0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctPoint>, Entity1)
	};
}

#endif // !_CadOpert2d_IntsctCutter_OrthClamped_Header
