#pragma once
#ifndef _AftApi_Model_Header
#define _AftApi_Model_Header

#include <memory>

namespace AutLib
{

	template<class ModelType, class SizeFun, class MetricFun = void>
	class AftApi_Model
	{

		/*Private Data*/

		std::shared_ptr<ModelType> theModel_;
		std::shared_ptr<SizeFun> theSize_;
		std::shared_ptr<MetricFun> theMetric_;
	};

	template<class ModelType, class SizeFun>
	class AftApi_Model<ModelType, SizeFun, void>
	{


	};
}

#endif // !_AftApi_Model_Header
