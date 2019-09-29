#pragma once
#ifndef _TModel_Tools_Header
#define _TModel_Tools_Header

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class TModel_Edge;
	class TModel_Surface;
	class TModel_Shell;

	class TModel_Tools
	{

	public:

		static std::vector<std::shared_ptr<TModel_Edge>> 
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
			);

		static std::shared_ptr<TModel_Surface>
			GetSurface
			(
				const TopoDS_Face& theFace
			);

		static std::vector<std::shared_ptr<TModel_Surface>>
			GetSurfaces
			(
				const TopoDS_Shape& theShape
			);

		static std::shared_ptr<std::vector<std::shared_ptr<TModel_Shell>>> TrackShells
		(
			const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
		);

		//- Warning: This function is on the early stage!
		static Standard_Boolean InnerHoles
		(
			const std::vector<std::shared_ptr<TModel_Shell>>& theShells,
			std::vector<std::shared_ptr<TModel_Shell>>& theInners,
			std::shared_ptr<TModel_Shell>& theOuters
		);

		static std::vector<std::shared_ptr<TModel_Edge>> 
			RetrieveNonSingularEdges
			(
				const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
			);
	};
}

#endif // !_TModel_Tools_Header
