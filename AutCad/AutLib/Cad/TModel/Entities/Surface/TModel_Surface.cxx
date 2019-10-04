#include <TModel_Surface.hxx>

#include <Entity2d_Metric1.hxx>
#include <Cad_Tools.hxx>
#include <TModel_Edge.hxx>
#include <TModel_Wire.hxx>

#include <Bnd_Box.hxx>
#include <Geom_BSplineSurface.hxx>

//- Private functions and operators

void AutLib::TModel_Surface::Check() const
{
	if (NOT theOuter_)
	{
		FatalErrorIn("void Check() const")
			<< "Invalid surface: has no outer wire!" << endl
			<< abort(FatalError);
	}

	if (NOT theGeom_)
	{
		FatalErrorIn("void Check() const")
			<< "Invalid surface: has no geometry!" << endl
			<< abort(FatalError);
	}
}

AutLib::Entity2d_Box 
AutLib::TModel_Surface::CalcParametricBoundingBox() const
{
	if (NOT theOuter_)
	{
		FatalErrorIn("Entity2d_Box CalcParametricBoundingBox() const")
			<< "Invalid surface: has no outer wire!" << endl
			<< abort(FatalError);
	}

	auto box = theOuter_->CalcParametricBoundingBox();
	return std::move(box);
}

AutLib::Entity3d_Box 
AutLib::TModel_Surface::CalcBoundingBox() const
{
	if (NOT theGeom_)
	{
		FatalErrorIn("Entity3d_Box CalcBoundingBox() const")
			<< "Invalid surface: has no geometry!" << endl
			<< abort(FatalError);
	}

	auto box = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(theGeom_, theBoundingBox_));
	return std::move(box);
}

//- constructors

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
	Check();

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
	Check();

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
	Check();

	theBoundingBox_ = CalcParametricBoundingBox();
	theBoundingBox3d_ = CalcBoundingBox();
}


//- public functions and operators

Standard_Boolean 
AutLib::TModel_Surface::IsBSpline() const
{
	return (Standard_Boolean)(Handle(Geom_BSplineSurface)::DownCast(Geometry()));
}

Standard_Boolean 
AutLib::TModel_Surface::IsClamped() const
{
	Debug_Null_Pointer(theOuter_);
	Debug_Null_Pointer(theOuter_->Edges());

	const auto& edges = *theOuter_->Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		if (NOT x->PairedEdge().lock()) return Standard_False;
	}
	return Standard_True;
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

AutLib::Entity2d_Metric1 
AutLib::TModel_Surface::MetricAt
(
	const Pnt2d & theCoord
) const
{
	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	theGeom_->D1(theCoord.X(), theCoord.Y(), Pt, D1U, D1V);

	auto A = D1U.Dot(D1U);
	auto B = D1U.Dot(D1V);
	auto C = D1V.Dot(D1V);

	Entity2d_Metric1 M(A, B, C);
	return std::move(M);
}

AutLib::Pnt3d 
AutLib::TModel_Surface::Value
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(theGeom_);
	auto p = theGeom_->Value(theCoord.X(), theCoord.Y());
	return std::move(p);
}

void AutLib::TModel_Surface::GetParametricBouns
(
	Standard_Real & theXmin, 
	Standard_Real & theXmax, 
	Standard_Real & theYmin,
	Standard_Real & theYmax
) const
{
	const auto& p0 = theBoundingBox_.P0();
	const auto& p1 = theBoundingBox_.P1();

	theXmin = p0.X();
	theXmax = p1.X();

	theYmin = p0.Y();
	theYmax = p1.Y();
}