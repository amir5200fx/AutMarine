#pragma once
#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class SurfPln>
	const std::shared_ptr<typename Mesh_SingularDetection<SurfPln>::singularZone>& 
		Mesh_SingularDetection<SurfPln>::Zone
		(
			const Standard_Integer theIndex
		) const
	{
		if (NOT INSIDE(theIndex, 0, NbZones() - 1))
		{
			FatalErrorIn("const std::shared_ptr<singularZone>& Zone(const Standard_Integer theIndex) const")
				<< "Invalid index: " << endl
				<< " - index: " << theIndex << endl
				<< " - nb. of zones: " << NbZones() << endl
				<< abort(FatalError);
		}
		return theZones_[theIndex];
	}

	template<class SurfPln>
	Standard_Boolean Mesh_SingularDetection<SurfPln>::IsHorizonsLoaded() const
	{
		return (Standard_Boolean)theHorizons_;
	}

	template<class SurfPln>
	Standard_Boolean Mesh_SingularDetection<SurfPln>::IsColorsLoaded() const
	{
		return (Standard_Boolean)theColors_;
	}

	template<class SurfPln>
	Standard_Boolean Mesh_SingularDetection<SurfPln>::IsSizeFunLoaded() const
	{
		return (Standard_Boolean)theSizeFun_;
	}

	template<class SurfPln>
	Standard_Boolean Mesh_SingularDetection<SurfPln>::IsInfoLoaded() const
	{
		return (Standard_Boolean)theInfo_;
	}
}