#pragma once
#ifndef _CrvMakerFreedom_Angle_Header
#define _CrvMakerFreedom_Angle_Header

#include <memory>

namespace AutLib
{

	template<class ParamAngle0, class ParamAngle1>
	class CrvMakerFreedom_Angle
	{

		/*Private Data*/

		std::shared_ptr<ParamAngle0> theParameter0_;
		std::shared_ptr<ParamAngle1> theParameter1_;

	public:

		CrvMakerFreedom_Angle
		(
			const std::shared_ptr<ParamAngle0>& theParameter0, 
			const std::shared_ptr<ParamAngle1>& theParameter1
		)
			: theParameter0_(theParameter0)
			, theParameter1_(theParameter1)
		{}

		const std::shared_ptr<ParamAngle0>& Parameter0() const
		{
			return theParameter0_;
		}

		const std::shared_ptr<ParamAngle1>& Parameter1() const
		{
			return theParameter1_;
		}
	};
}

#endif // !_CrvMakerFreedom_Angle_Header
