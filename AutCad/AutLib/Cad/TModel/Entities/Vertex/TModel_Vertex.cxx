#include <TModel_Vertex.hxx>

#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void AutLib::TModel_Vertex::ImportToSurfaces_dup
(
	const Standard_Integer theIndex, 
	const std::weak_ptr<TModel_Surface>& theFace
)
{
	auto Iter = theEdges_.find(theIndex);
	if (Iter IS_EQUAL theEdges_.end())
	{
		theFaces_.insert(std::make_pair(theIndex, theFace));
	}
}

void AutLib::TModel_Vertex::RemoveFromEdges
(
	const Standard_Integer theIndex
)
{
	auto Iter = theEdges_.find(theIndex);
	if (Iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn("void RemoveFromEdges(const Standard_Integer theIndex)")
			<< "The edge is not in the list" << endl
			<< abort(FatalError);
	}

	theEdges_.erase(Iter);
}

void AutLib::TModel_Vertex::RemoveFromFaces
(
	const Standard_Integer theIndex
)
{
	auto Iter = theFaces_.find(theIndex);
	if (Iter IS_EQUAL theFaces_.end())
	{
		FatalErrorIn("void RemoveFromFaces(const Standard_Integer theIndex)")
			<< "The edge is not in the list" << endl
			<< abort(FatalError);
	}

	theFaces_.erase(Iter);
}