#include <TModel_Plane.hxx>

#include <TModel_Surface.hxx>
#include <TModel_parWire.hxx>
#include <TModel_Wire.hxx>
#include <TModel_Edge.hxx>
#include <TModel_parCurve.hxx>

namespace AutLib
{

	static std::shared_ptr<TModel_parWire> GetWire(const TModel_Wire& theWire)
	{
		auto curves_ptr =
			std::make_shared<std::vector<std::shared_ptr<TModel_parCurve>>>();
		auto& curves = *curves_ptr;
		curves.reserve(theWire.NbEdges());

		Standard_Integer K = 0;
		for (const auto& x : *theWire.Edges())
		{
			Debug_Null_Pointer(x);

			const auto& xCurve = x->Par();
			Debug_Null_Pointer(xCurve);

			curves.push_back(xCurve);
		}

		auto wire =
			std::make_shared<TModel_parWire>(curves_ptr);

		return std::move(wire);
	}
}

void AutLib::TModel_Plane::RetrieveWiresTo
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

//- Static functions and operators

std::shared_ptr<AutLib::TModel_Plane>
AutLib::TModel_Plane::MakePlane
(
	const TModel_Surface & theFace
)
{
	if (NOT theFace.OuterWire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Face : has no outer wire" << endl
			<< abort(FatalError);
	}

	const auto& Outer = *theFace.OuterWire();
	const auto& Inners = *theFace.InnerWires();

	auto outer_wire =
		GetWire(Outer);

	std::shared_ptr<std::vector<std::shared_ptr<TModel_parWire>>> inner_wires;
	if (theFace.InnerWires())
	{
		inner_wires = std::make_shared<std::vector<std::shared_ptr<TModel_parWire>>>();
		inner_wires->reserve(Inners.size());

		for (const auto& x : Inners)
		{
			Debug_Null_Pointer(x);

			auto wire = GetWire(*x);
			inner_wires->push_back(wire);
		}
	}

	auto plane =
		std::make_shared<TModel_Plane>(outer_wire, inner_wires);
	return std::move(plane);
}