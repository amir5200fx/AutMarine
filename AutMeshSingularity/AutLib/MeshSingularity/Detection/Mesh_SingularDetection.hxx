#pragma once
#ifndef _Mesh_SingularDetection_Header
#define _Mesh_SingularDetection_Header

#include <Global_Done.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Mesh_SingularDetection_Info.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Mesh_SingularHorizon;
	class CadAnalys_ColoringSurfMetric;
	class Mesh_SingularDetection_Info;

	template<class SurfPln>
	class Mesh_SingularZone;

	template<class SurfPln>
	class Mesh_SingularDetection
		: public Global_Done
	{

		typedef Mesh_SingularDetection_Info info;
		typedef Mesh_SingularZone<SurfPln> singularZone;
		typedef std::vector<std::shared_ptr<singularZone>> zoneList;

		/*Private Data*/

		std::shared_ptr<Mesh_SingularHorizon> theHorizons_;
		std::shared_ptr<CadAnalys_ColoringSurfMetric> theColors_;

		std::shared_ptr<Geo3d_SizeFunction> theSizeFun_;

		std::shared_ptr<info> theInfo_;


		zoneList theZones_;


		//- private function and operators

		zoneList& ChangeZones()
		{
			return theZones_;
		}

	public:

		Mesh_SingularDetection()
		{}

		Standard_Integer NbZones() const
		{
			return (Standard_Integer)theZones_.size();
		}

		const zoneList& Zones() const
		{
			return theZones_;
		}

		const std::shared_ptr<Mesh_SingularHorizon>& Horizons() const
		{
			return theHorizons_;
		}

		const std::shared_ptr<singularZone>& Zone(const Standard_Integer theIndex) const;

		const std::shared_ptr<CadAnalys_ColoringSurfMetric>& Colors() const
		{
			return theColors_;
		}

		const std::shared_ptr<Geo3d_SizeFunction>& SizeFunction() const
		{
			return theSizeFun_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		Standard_Boolean IsHorizonsLoaded() const;

		Standard_Boolean IsColorsLoaded() const;

		Standard_Boolean IsSizeFunLoaded() const;

		Standard_Boolean IsInfoLoaded() const;

		void LoadHorizons(const std::shared_ptr<Mesh_SingularHorizon>& theHorizons)
		{
			theHorizons_ = theHorizons;
		}

		void LoadColors(const std::shared_ptr<CadAnalys_ColoringSurfMetric>& theColors)
		{
			theColors_ = theColors;
		}

		void LoadSizeFunction(const std::shared_ptr<Geo3d_SizeFunction>& theFun)
		{
			theSizeFun_ = theFun;
		}

		void LoadInfo(const std::shared_ptr<info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void Perform();

		void ExportToPlt(OFstream& File) const;
	};
}

#include <Mesh_SingularDetectionI.hxx>

#endif // !_Mesh_SingularDetection_Header
