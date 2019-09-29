#include <TModel_Surface.hxx>

#include <TModel_Edge.hxx>
#include <TModel_Wire.hxx>

AutLib::TModel_Surface::TModel_Surface
(
	const Handle(Geom_Surface)& theGeom,
	const outer & theOuter,
	const inner & theInner
) 
: theGeom_(theGeom)
, theOuter_(theOuter)
, theInner_(theInner)
{
	theBoundingBox_ = CalcParametricBoundingBox();
	theBoundingBox3d_ = CalcBoundingBox();
}

AutLib::TModel_Surface::TModel_Surface
(
	const Standard_Integer theIndex, 
	const Handle(Geom_Surface)& theGeom,
	const outer & theOuter,
	const inner & theInner
)
	: theGeom_(theGeom)
	, theOuter_(theOuter)
	, theInner_(theInner)
	, TModel_Entity(theIndex)
{
	theBoundingBox_ = CalcParametricBoundingBox();
	theBoundingBox3d_ = CalcBoundingBox();
}

AutLib::TModel_Surface::TModel_Surface
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom_Surface)& theGeom, 
	const outer & theOuter,
	const inner & theInner
)
	: theGeom_(theGeom)
	, theOuter_(theOuter)
	, theInner_(theInner)
	, TModel_Entity(theIndex, theName)
{
	theBoundingBox_ = CalcParametricBoundingBox();
	theBoundingBox3d_ = CalcBoundingBox();
}

std::vector<std::shared_ptr<AutLib::TModel_Edge>> 
AutLib::TModel_Surface::Edges() const
{
	if (NOT theOuter_)
	{
		FatalErrorIn("std::vector<std::shared_ptr<TModel_Edge>> Edges() const")
			<< "Invalid Surface: There is no outer wire for the surface" << endl
			<< abort(FatalError);
	}

	auto size = theOuter_->NbEdges();
	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			size += x->NbEdges();
		}
	}

	if (NOT size)
	{
		FatalErrorIn("std::vector<std::shared_ptr<TModel_Edge>> Edges() const")
			<< "Invalid Surface: the surface has no edge" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<AutLib::TModel_Edge>> edges;
	edges.reserve(size);

	Debug_Null_Pointer(theOuter_->Edges());
	const auto& OuterEdges = *theOuter_->Edges();

	for (const auto& x : OuterEdges)
	{
		edges.push_back(x);
	}

	if (NOT theInner_)
	{
		return std::move(edges);
	}

	for (const auto& x : *theInner_)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Edges());
		for (const auto& edge : *x->Edges())
		{
			edges.push_back(edge);
		}
	}
	return std::move(edges);
}