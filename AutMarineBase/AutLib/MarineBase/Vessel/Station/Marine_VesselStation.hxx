#pragma once
#ifndef _Marine_VesselStation_Header
#define _Marine_VesselStation_Header

#include <Marine_CompoundSectionFwd.hxx>
#include <Entity2d_Box.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace AutLib
{

	class Marine_VesselStation
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::shared_ptr<marineLib::cmpSectCurve> theCurve_;


		Entity2d_Box theBox_;

	public:

		Marine_VesselStation()
		{}


	};
}

#endif // !_Marine_VesselStation_Header
