#pragma once
#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <vector>
namespace AutLib
{

	/*template<class RegionType, class SizeFun, class MetricFun>
	void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()
	{
		if (NOT MetricFunction())
		{
			FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
				<< " no metric function has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT SizeFunction())
		{
			FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
				<< " no size function has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT Plane())
		{
			FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
				<< " no plane has been loaded!" << endl
				<< abort(FatalError);
		}

		std::vector<std::shared_ptr<typename RegionType::plnWire>> wires;
		Plane()->RetrieveWiresTo(wires);
		if (wires.empty())
		{
			FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
				<< " Invalid plane: wire list is empty" << endl
				<< abort(FatalError);
		}


	}*/
}