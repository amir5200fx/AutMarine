#include <Cad3d_TModel.hxx>

#include <Entity3d_Chain.hxx>
#include <Merge3d_Chain.hxx>
#include <TModel_Curve.hxx>
#include <TModel_Edge.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	namespace tModel
	{

		
	}
}

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