#include <Mesh2d_gPatch.hxx>

#include <Mesh2d_gPlnRegionSurface.hxx>

namespace AutLib
{

	template<>
	std::shared_ptr<Mesh2d_gPlnRegionSurface> Mesh2d_gPatch::GetPlane() const
	{
		auto This = 
			std::dynamic_pointer_cast<Mesh2d_gPatch>
			(
				std::const_pointer_cast<GModel_Surface>(this->shared_from_this())
				);
		auto plane = Mesh2d_gPlnRegionSurface::MakePlane(This);
		return std::move(plane);
	}
}