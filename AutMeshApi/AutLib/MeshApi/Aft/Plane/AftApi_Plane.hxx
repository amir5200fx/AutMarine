#pragma once
#ifndef _AftApi_Plane_Header
#define _AftApi_Plane_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>
#include <Entity2d_Triangulation.hxx>

#include <memory>

namespace AutLib
{

	template<class PlaneType, class AftMetricPrcsr>
	class AftApi_Plane
		: public Global_Done
		, public Global_Verbose
	{

		/*Private Data*/

		std::shared_ptr<PlaneType> thePlane_;
		std::shared_ptr<AftMetricPrcsr> theMetricMap_;

		std::shared_ptr<Entity2d_Triangulation> theMesh_;


		std::shared_ptr<Entity2d_Triangulation>& ChangeMesh()
		{
			return theMesh_;
		}

	public:

		AftApi_Plane()
		{}

		AftApi_Plane
		(
			const std::shared_ptr<PlaneType>& thePlane, 
			const std::shared_ptr<AftMetricPrcsr>& theMetricMap
		)
			: thePlane_(thePlane)
			, theMetricMap_(theMetricMap)
		{}

		const std::shared_ptr<PlaneType>& Plane() const
		{
			return thePlane_;
		}

		const std::shared_ptr<AftMetricPrcsr>& MetricMap() const
		{
			return theMetricMap_;
		}

		const std::shared_ptr<Entity2d_Triangulation>& Mesh() const
		{
			return theMesh_;
		}

		void Perform();

		void LoadPlane(const std::shared_ptr<PlaneType>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void LoadMetricMap(const std::shared_ptr<AftMetricPrcsr>& theMap)
		{
			theMetricMap_ = theMap;
		}

		

	};
}

#include <AftApi_PlaneI.hxx>

#endif // !_AftApi_Plane_Header
