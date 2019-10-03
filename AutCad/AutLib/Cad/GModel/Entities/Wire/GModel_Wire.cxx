#include <GModel_Wire.hxx>

#include <GModel_parCurve.hxx>
#include <GModel_parWire.hxx>
#include <GModel_Edge.hxx>
#include <Entity2d_Box.hxx>

AutLib::Entity2d_Box
AutLib::GModel_Wire::CalcParametricBoundingBox() const
{
	Debug_Null_Pointer(theEdges_);

	const auto& edges = *theEdges_;

	if (edges.empty())
	{
		FatalErrorIn("Entity2d_Box CalcParametricBoundingBox() const")
			<< "the edge list is empty" << endl
			<< abort(FatalError);
	}

	auto box = edges[0]->Par()->BoundingBox();
	forThose(Index, 1, edges.size() - 1)
	{
		box = Entity2d_Box::Union(edges[Index]->Par()->BoundingBox(), box);
	}
	return std::move(box);
}


//- Static function and operators

std::shared_ptr<std::vector<std::shared_ptr<AutLib::GModel_parCurve>>> 
AutLib::GModel_Wire::RetrievePlaneCurves
(
	const GModel_Wire & theWire
)
{
	auto curves = std::make_shared<std::vector<std::shared_ptr<GModel_parCurve>>>();
	curves->reserve(theWire.NbEdges());

	for (const auto& x : *theWire.Edges())
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Par());

		curves->push_back(x->Par());
	}
	return std::move(curves);
}

std::shared_ptr<AutLib::GModel_parWire> 
AutLib::GModel_Wire::RetrieveParWire
(
	const GModel_Wire & theWire
)
{
	auto wire = std::make_shared<GModel_parWire>(RetrievePlaneCurves(theWire));
	return std::move(wire);
}