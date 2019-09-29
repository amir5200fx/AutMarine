#include <TModel_Shell.hxx>

#include <Entity3d_Box.hxx>
#include <TModel_Surface.hxx>

AutLib::TModel_Shell::TModel_Shell
(
	const std::shared_ptr<surfaceList>& theSurfaces
)
	: theSurfaces_(theSurfaces)
{
	WaterTightCondition();

	CalcBoundingBox();
}

AutLib::TModel_Shell::TModel_Shell
(
	const Standard_Integer theIndex,
	const std::shared_ptr<surfaceList>& theSurfaces
)
	: TModel_Entity(theIndex)
	, theSurfaces_(theSurfaces)
{
	WaterTightCondition();

	CalcBoundingBox();
}

AutLib::TModel_Shell::TModel_Shell
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<surfaceList>& theSurfaces
)
	: TModel_Entity(theIndex, theName)
	, theSurfaces_(theSurfaces)
{
	WaterTightCondition();

	CalcBoundingBox();
}

void AutLib::TModel_Shell::WaterTightCondition()
{
	Debug_Null_Pointer(theSurfaces_);
	for (const auto& x : *theSurfaces_)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsClamped())
		{
			IsWaterTight_ = Standard_False;
			return;
		}
	}
	IsWaterTight_ = Standard_True;
}

void AutLib::TModel_Shell::CalcBoundingBox()
{
	Debug_Null_Pointer(theSurfaces_);
	const auto& surfaces = *theSurfaces_;

	if (surfaces.empty())
	{
		FatalErrorIn("void CalcBoundingBox()")
			<< "the surface list is empty" << endl
			<< abort(FatalError);
	}

	auto box = surfaces[0]->BoundingBox3d();
	forThose(Index, 1, surfaces.size() - 1)
	{
		Debug_Null_Pointer(surfaces[Index]);
		box = Entity3d_Box::Union(box, surfaces[Index]->BoundingBox3d());
	}

	theBoundingBox_ = std::move(box);
}