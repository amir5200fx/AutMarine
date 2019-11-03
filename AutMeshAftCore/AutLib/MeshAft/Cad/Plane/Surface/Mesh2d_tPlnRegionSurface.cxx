#include <Mesh2d_tPlnRegionSurface.hxx>

#include <TModel_Surface.hxx>
#include <TModel_Wire.hxx>
#include <TModel_Edge.hxx>

namespace AutLib
{

	void Mesh_PlnRegion<TModel_parCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>::RetrieveWiresTo
	(
		wireList & theWires
	) const
	{
		theWires.push_back(theOutter_);
		if (theInner_)
		{
			for (const auto& x : *theInner_)
			{
				theWires.push_back(x);
			}
		}
	}

	std::shared_ptr<typename Mesh2d_tPlnRegionSurface::plnWireType> 
		Mesh_PlnRegion<TModel_parCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>::MakeMeshWire
		(
			const TModel_Wire & theWire
		)
	{
		auto curves_ptr =
			std::make_shared<std::vector<std::shared_ptr<plnCurveType>>>();
		auto& curves = *curves_ptr;
		curves.reserve(theWire.NbEdges());

		Standard_Integer K = 0;
		for (const auto& x : *theWire.Edges())
		{
			Debug_Null_Pointer(x);

			const auto& xCurve = x->Par();
			Debug_Null_Pointer(xCurve);

			curves.push_back(std::make_shared<plnCurveType>(*xCurve));
		}

		auto wire =
			std::make_shared<plnWireType>(curves_ptr);

		return std::move(wire);
	}

	std::shared_ptr<Mesh2d_tPlnRegionSurface> 
		Mesh_PlnRegion<TModel_parCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>::MakePlane
		(
			const std::shared_ptr<TModel_Surface> & theSurface
		)
	{
		Debug_Null_Pointer(theSurface);
		if (NOT theSurface->OuterWire())
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid surface : has no outer wire" << endl
				<< abort(FatalError);
		}

		const auto& Outer = *theSurface->OuterWire();
		const auto& Inners = *theSurface->InnerWires();

		auto outer_wire =
			MakeMeshWire(Outer);

		std::shared_ptr<std::vector<std::shared_ptr<plnWireType>>> 
			inner_wires;
		if (theSurface->InnerWires())
		{
			inner_wires = 
				std::make_shared<std::vector<std::shared_ptr<plnWireType>>>();
			inner_wires->reserve(Inners.size());

			for (const auto& x : Inners)
			{
				Debug_Null_Pointer(x);

				auto wire = MakeMeshWire(*x);
				inner_wires->push_back(wire);
			}
		}

		auto plane = 
			std::make_shared<Mesh2d_tPlnRegionSurface>
			(
				theSurface, outer_wire, 
				inner_wires);
		return std::move(plane);
	}
}