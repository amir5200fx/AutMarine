#include <Mesh2d_tPatch.hxx>

#include <Mesh2d_tPlnRegionSurface.hxx>
#include <TModel_Surface.hxx>

namespace AutLib
{

	template<>
	std::shared_ptr<Mesh2d_tPlnRegionSurface> Mesh2d_tPatch::GetPlane() const
	{
		auto This =
			std::dynamic_pointer_cast<Mesh2d_tPatch>
			(
				std::const_pointer_cast<TModel_Entity>(this->shared_from_this())
				);
		auto plane = Mesh2d_tPlnRegionSurface::MakePlane(This);
		return std::move(plane);
	}
}