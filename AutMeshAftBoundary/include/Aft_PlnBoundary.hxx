#pragma once
#ifndef _Aft_PlnBoundary_Header
#define _Aft_PlnBoundary_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace AutLib
{

	

	template<class RegionType, class SizeFun, class MetricFun = void>
	class Aft_PlnBoundary
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<SizeFun> theSizeFun_;
		std::shared_ptr<MetricFun> theMetricFun_;

		std::shared_ptr<RegionType> thePlane_;

	public:

		Aft_PlnBoundary()
		{}

		const std::shared_ptr<SizeFun>& SizeFunction() const
		{
			return theSizeFun_;
		}

		const std::shared_ptr<MetricFun>& MetricFunction() const
		{
			return theMetricFun_;
		}

		const std::shared_ptr<RegionType>& Plane() const
		{
			return thePlane_;
		}

		void Perform();

		void LoadSizeFunction(const std::shared_ptr<SizeFun>& theFun)
		{
			theSizeFun_ = theFun;
		}

		void LoadMetricFunction(const std::shared_ptr<MetricFun>& theFun)
		{
			theMetricFun_ = theFun;
		}

		void LoadPlane(const std::shared_ptr<RegionType>& thePlane)
		{
			thePlane_ = thePlane;
		}
	};

	template<class RegionType, class SizeFun>
	class Aft_PlnBoundary<RegionType, SizeFun, void>
	{

		/*Private Data*/

		std::shared_ptr<SizeFun> theSizeFun_;

		std::shared_ptr<RegionType> thePlane_;

	public:

		Aft_PlnBoundary()
		{}

		const std::shared_ptr<SizeFun>& SizeFunction() const
		{
			return theSizeFun_;
		}

		const std::shared_ptr<RegionType>& Plane() const
		{
			return thePlane_;
		}

		void Perform();

		void LoadSizeFunction(const std::shared_ptr<SizeFun>& theFun)
		{
			theSizeFun_ = theFun;
		}

		void LoadPlane(const std::shared_ptr<RegionType>& thePlane)
		{
			thePlane_ = thePlane;
		}
	};
}

#include <Aft_PlnBoundaryI.hxx>

#endif // !_Aft_PlnBoundary_Header
