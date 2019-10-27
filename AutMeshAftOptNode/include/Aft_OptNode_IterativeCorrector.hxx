#pragma once
#ifndef _Aft_OptNode_IterativeCorrector_Header
#define _Aft_OptNode_IterativeCorrector_Header

#include <Aft_OptNode_Corrector.hxx>
#include <Aft_OptNode_IterativeCorrectorInfo.hxx>

#include <memory>

namespace AutLib
{

	template<class AftMetricPrcsr>
	class Aft_OptNode_IterativeCorrector
		: public Aft_OptNode_Corrector<AftMetricPrcsr>
	{

	public:

		typedef Aft_OptNode_Corrector<AftMetricPrcsr> base;

		typedef typename AftMetricPrcsr::frontType frontType;
		typedef typename AftMetricPrcsr::sizeFun sizeFun;
		typedef typename AftMetricPrcsr::metricFun metricFun;

		typedef typename sizeFun::ptType Point;

	private:

		/*Private Data*/

		const std::shared_ptr<AftMetricPrcsr>& theMetricMap_;

		const std::shared_ptr<Aft_OptNode_IterativeCorrectorInfo>& theInfo_;

	public:

		Aft_OptNode_IterativeCorrector
		(
			const Standard_Real theSize,
			const frontType& theFront,
			const Point& theP0,
			const std::shared_ptr<AftMetricPrcsr>& theMetricMap,
			const std::shared_ptr<Aft_OptNode_IterativeCorrectorInfo>& theInfo
		)
			: Aft_OptNode_Corrector<AftMetricPrcsr>(theSize, theFront, theP0)
			, theMetricMap_(theMetricMap)
			, theInfo_(theInfo)
		{}


		const std::shared_ptr<AftMetricPrcsr>& MetricMap() const
		{
			return theMetricMap_;
		}

		const std::shared_ptr<Aft_OptNode_IterativeCorrectorInfo>& Info() const
		{
			return theInfo_;
		}

		void Perform() override;
	};
}

#include <Aft_OptNode_IterativeCorrectorI.hxx>

#endif // !_Aft_OptNode_IterativeCorrector_Header
