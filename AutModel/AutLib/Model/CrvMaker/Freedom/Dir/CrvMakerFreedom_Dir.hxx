#pragma once
#ifndef _CrvMakerFreedom_Dir_Header
#define _CrvMakerFreedom_Dir_Header

#include <memory>

namespace AutLib
{

	template<class ParamDir0, class ParamDir1>
	class CrvMakerFreedom_Dir
	{

		/*Private Data*/

		std::shared_ptr<ParamDir0> theParameter0_;
		std::shared_ptr<ParamDir1> theParameter1_;

	public:

		CrvMakerFreedom_Dir
		(
			const std::shared_ptr<ParamDir0>& theParameter0,
			const std::shared_ptr<ParamDir1>& theParameter1
		)
			: theParameter0_(theParameter0)
			, theParameter1_(theParameter1)
		{}

		const std::shared_ptr<ParamDir0>& Parameter0() const
		{
			return theParameter0_;
		}

		const std::shared_ptr<ParamDir1>& Parameter1() const
		{
			return theParameter1_;
		}
	};
}

#endif // !_CrvMakerFreedom_Dir_Header
