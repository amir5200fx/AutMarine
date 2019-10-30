#pragma once
#ifndef _AftApi_Plane_Header
#define _AftApi_Plane_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>
#include <Entity2d_Triangulation.hxx>
#include <MeshApi_Aft.hxx>
#include <Aft2d_CoreTemplate.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Cad2d_Plane;

	template<class OptNodeAlg, class AftMetricPrcsr>
	class MeshApi_Aft<Cad2d_Plane, OptNodeAlg, AftMetricPrcsr, false>
		: public Global_Done
		, public Global_Verbose
		, public Aft2d_CoreTemplate<OptNodeAlg, AftMetricPrcsr>
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_Plane> thePlane_;
		std::shared_ptr<AftMetricPrcsr> theMetricMap_;


		std::shared_ptr<Entity2d_Triangulation> theMesh_;


		std::shared_ptr<Entity2d_Triangulation>& ChangeMesh()
		{
			return theMesh_;
		}

	public:

		MeshApi_Aft()
		{}

		MeshApi_Aft
		(
			const std::shared_ptr<Cad2d_Plane>& thePlane,
			const std::shared_ptr<AftMetricPrcsr>& theMetricMap
		)
			: thePlane_(thePlane)
			, theMetricMap_(theMetricMap)
		{}

		const std::shared_ptr<Cad2d_Plane>& Plane() const
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

		void LoadPlane(const std::shared_ptr<Cad2d_Plane>& thePlane)
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
