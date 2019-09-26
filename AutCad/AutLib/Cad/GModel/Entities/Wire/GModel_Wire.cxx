#include <GModel_Wire.hxx>

#include <GModel_parCurve.hxx>
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