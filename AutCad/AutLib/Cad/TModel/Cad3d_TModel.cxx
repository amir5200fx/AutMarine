#include <Cad3d_TModel.hxx>

#include <Entity3d_Chain.hxx>
#include <Merge3d_Chain.hxx>
#include <TModel_Curve.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Edge.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Shell.hxx>
#include <TModel_Tools.hxx>
#include <TModel_EntityBlock.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	namespace tModel
	{

		
	}
}

//- Private functions and operators

AutLib::Entity3d_Box 
AutLib::Cad3d_TModel::CalcBoundingBox
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	if (theSurfaces.empty())
	{
		FatalErrorIn("Entity3d_Box CalcBoundingBox()")
			<< "the solid has no face!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theSurfaces[0]);

	auto box = theSurfaces[0]->BoundingBox3d();
	forThose(Index, 1, theSurfaces.size() - 1)
	{
		Debug_Null_Pointer(theSurfaces[Index]);

		box = Entity3d_Box::Union(box, theSurfaces[Index]->BoundingBox3d());
	}
	return std::move(box);
}


//- public functions and operators

Standard_Integer 
AutLib::Cad3d_TModel::NbFreeSegment() const
{
	Debug_Null_Pointer(theEdges_);

	std::vector<std::shared_ptr<TModel_Entity>> entities;
	theEdges_->RetrieveTo(entities);

	Standard_Integer K = 0;
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		auto paired = std::dynamic_pointer_cast<TModel_Paired>(x);

		Debug_Null_Pointer(paired);
		if (NOT paired->IsPaired()) ++K;
	}
	return K;
}

Standard_Boolean 
AutLib::Cad3d_TModel::HasFreeSegment() const
{
	Debug_Null_Pointer(theEdges_);

	std::vector<std::shared_ptr<TModel_Entity>> entities;
	theEdges_->RetrieveTo(entities);

	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		auto paired = std::dynamic_pointer_cast<TModel_Paired>(x);

		Debug_Null_Pointer(paired);
		if (NOT paired->IsPaired()) return Standard_True;
	}
	return Standard_False;
}

void AutLib::Cad3d_TModel::RetrieveFacesTo
(
	std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
) const
{
	std::vector<std::shared_ptr<TModel_Entity>> entities;
	theSurfaces_->RetrieveTo(entities);

	theSurfaces.reserve(entities.size());
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		auto surface = std::dynamic_pointer_cast<TModel_Surface>(x);

		theSurfaces.push_back(std::move(surface));
	}
}

void AutLib::Cad3d_TModel::RetrieveSegmentsTo
(
	std::vector<std::shared_ptr<TModel_Paired>>& theEdges
) const
{
	std::vector<std::shared_ptr<TModel_Entity>> entities;
	theEdges_->RetrieveTo(entities);

	theEdges.reserve(entities.size());
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		auto edge = std::dynamic_pointer_cast<TModel_Paired>(x);

		theEdges.push_back(std::move(edge));
	}
}

void AutLib::Cad3d_TModel::RetrieveCornersTo
(
	std::vector<std::shared_ptr<TModel_Vertex>>& thevertices
) const
{
	std::vector<std::shared_ptr<TModel_Entity>> entities;
	theVertices_->RetrieveTo(entities);

	thevertices.reserve(entities.size());
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		auto vertex = std::dynamic_pointer_cast<TModel_Vertex>(x);

		thevertices.push_back(std::move(vertex));
	}
}

//- static functions and operators

Standard_Boolean 
AutLib::Cad3d_TModel::MakeShells
(
	const std::shared_ptr<Cad3d_TModel>& theSolid
)
{
	std::vector<std::shared_ptr<TModel_Surface>> surfaces;
	theSolid->RetrieveFacesTo(surfaces);
	
	auto pShells = TModel_Tools::TrackShells(surfaces);
	for (const auto& x : *pShells)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsWaterTight())
		{
			theSolid->theInner_ = pShells;
			return Standard_True;
		}
	}

	theSolid->theInner_ = std::make_shared<shellList>();
	if (TModel_Tools::InnerHoles(*pShells, *theSolid->theInner_, theSolid->theOuter_))
	{
		return Standard_True;
	}
	return Standard_False;
}

void AutLib::Cad3d_TModel::SplitByShells
(
	const std::shared_ptr<Cad3d_TModel>& theSolid
)
{
	if (NOT theSolid->theOuter_)
	{
		return;
	}

	const auto& faces = theSolid->theSurfaces_;
	if (faces->NbBlocks() NOT_EQUAL 1)
	{
		FatalErrorIn("void Cad3d_TModel::SplitByShells()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theSolid->theInner_);
	if (theSolid->theInner_->empty())
	{
		return;
	}

	std::vector<std::shared_ptr<TModel_EntityBlock>> blocks;
	faces->RetrieveTo(blocks);

	Debug_If_Condition_Message(blocks.size() NOT_EQUAL 1, "Conflict Data");
	const auto& block = faces->SelectBlockEntity(blocks[0]->Name());

	const auto& innerShells = *theSolid->theInner_;

	Standard_Integer K = 0;
	for (const auto& x : innerShells)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Surfaces());

		const auto& surfaces = *x->Surfaces();
		for (const auto& s : surfaces)
		{
			Debug_Null_Pointer(s);
			block->SelectEntity(s->Index());
		}

		faces->Split("Default Inner Shell " + std::to_string((++K) + 1));
	}

	if (NOT block->NbEntities())
	{
		FatalErrorIn("void Cad3d_TModel::SplitByShells()")
			<< "Conflict Data"
			<< abort(FatalError);
	}
}