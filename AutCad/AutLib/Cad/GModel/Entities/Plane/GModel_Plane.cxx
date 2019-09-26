#include <GModel_Plane.hxx>

#include <GModel_Surface.hxx>
#include <GModel_parWire.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Edge.hxx>
#include <GModel_parCurve.hxx>

namespace AutLib
{

	static std::shared_ptr<GModel_parWire> GetWire(const GModel_Wire& theWire)
	{
		auto curves_ptr =
			std::make_shared<std::vector<std::shared_ptr<GModel_parCurve>>>();
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
			std::make_shared<GModel_parWire>(curves_ptr);

		return std::move(wire);
	}
}

void AutLib::GModel_Plane::RetrieveWiresTo
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

std::shared_ptr<AutLib::GModel_Plane>
AutLib::GModel_Plane::MakePlane
(
	const GModel_Surface & theFace
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

	std::shared_ptr<std::vector<std::shared_ptr<GModel_parWire>>> inner_wires;
	if (theFace.InnerWires())
	{
		inner_wires = std::make_shared<std::vector<std::shared_ptr<GModel_parWire>>>();
		inner_wires->reserve(Inners.size());

		for (const auto& x : Inners)
		{
			Debug_Null_Pointer(x);

			auto wire = GetWire(*x);
			inner_wires->push_back(wire);
		}
	}

	auto plane =
		std::make_shared<GModel_Plane>(outer_wire, inner_wires);
	return std::move(plane);
}