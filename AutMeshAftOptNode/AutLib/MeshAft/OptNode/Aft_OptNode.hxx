#pragma once
#ifndef _Aft_OptNode_Header
#define _Aft_OptNode_Header

#include <Standard_TypeDef.hxx>
#include <Aft_MetricPrcsr.hxx>

#include <memory>

namespace AutLib
{

	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_OptNode_Base
	{

		typedef Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>
			metricMap;
		typedef FrontType frontType;
		typedef typename SizeFun::ptType Point;

		/*Private Data*/

		const std::shared_ptr<metricMap>& theMetricMap_;

		Standard_Real theSize_;

		const frontType& theFront_;

		Point theCoord_;

		Standard_Boolean IsConverged_;

	protected:

		Aft_OptNode_Base
		(
			const std::shared_ptr<metricMap>& theMetricMap,
			const Standard_Real theSize,
			const frontType& theFront
		)
			: theMetricMap_(theMetricMap)
			, theSize_(theSize)
			, theFront_(theFront)
		{}


		Point& ChangeCoord()
		{
			return theCoord_;
		}

		Standard_Boolean& Change_IsConverged()
		{
			return IsConverged_;
		}

	public:

		const std::shared_ptr<metricMap>& MetricMap() const
		{
			return theMetricMap_;
		}

		Standard_Real ElementSize() const
		{
			return theSize_;
		}

		const frontType& Front() const
		{
			return theFront_;
		}

		const Point& Coord() const
		{
			return theCoord_;
		}

	};

	template
		<
		class FrontType,
		class SizeFun,
		class OptTraits = void,
		bool CorrAlg = false,
		class MetricFun = void,
		class AltrAlg = void
		>
		class Aft_OptNode
		: public Global_Done
		, public Aft_OptNode_Base<FrontType, sizeFun, MetricFun>
	{

		typedef Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>
			metricMap;
		typedef FrontType frontType;
		typedef MetricFun metricFun;
		typedef SizeFun sizeFun;

		typedef typename sizeFun::ptType Point;

		/*Private Data*/

	public:

		Aft_OptNode
		(
			const std::shared_ptr<metricMap>& theMetricMap,
			const Standard_Real theSize,
			const frontType& theFront
		)
			: theMetricMap_(theMetricMap)
			, theSize_(theSize)
			, theFront_(theFront)
		{}

		void Perform();
	};

	template<class FrontType, class SizeFun>
	class Aft_OptNode<FrontType, SizeFun>
		: public Global_Done
		, public Aft_OptNode_Base<frontType, sizeFun, void>
	{

		typedef Aft_OptNode_Base<frontType, sizeFun, void> base;
		typedef Aft_MetricPrcsr<FrontType, SizeFun, void>
			metricMap;
		typedef FrontType frontType;
		typedef SizeFun sizeFun;

		typedef typename sizeFun::ptType Point;

		/*Private Data*/


		//- private functions and operators

	public:

		Aft_OptNode
		(
			const std::shared_ptr<metricMap>& theMetricMap,
			const Standard_Real theSize,
			const frontType& theFront
		)
			: theMetricMap_(theMetricMap)
			, theSize_(theSize)
			, theFront_(theFront)
		{}

		void Perform();
	};

	template<class FrontType, class SizeFun, class OptTraits>
	class Aft_OptNode<FrontType, SizeFun, OptTraits, true>
		: public Global_Done
		, public Aft_OptNode_Base<frontType, sizeFun, void>
	{

		typedef Aft_OptNode_Base<frontType, sizeFun, void> base;
		typedef Aft_MetricPrcsr<FrontType, SizeFun, void>
			metricMap;
		typedef FrontType frontType;
		typedef SizeFun sizeFun;

		typedef typename sizeFun::ptType Point;

		/*Private Data*/


		//- private functions and operators

	public:

		Aft_OptNode
		(
			const std::shared_ptr<metricMap>& theMetricMap,
			const Standard_Real theSize,
			const frontType& theFront
		)
			: theMetricMap_(theMetricMap)
			, theSize_(theSize)
			, theFront_(theFront)
		{}

		void Perform();
	};
}

#include <Aft_OptNodeI.hxx>

#endif // !_Mesh_AftOptNode_Header
