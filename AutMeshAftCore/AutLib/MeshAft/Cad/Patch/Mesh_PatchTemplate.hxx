#pragma once
#ifndef _Mesh_PatchTemplate_Header
#define _Mesh_PatchTemplate_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Numeric_AdaptIntegrationInfo;

	template<class PlnWireType>
	class Mesh_PlnRegion;

	template<class SurfType>
	class Mesh_PatchTemplate
		: public SurfType
	{

		typedef Numeric_AdaptIntegrationInfo intgInfo;

		/*Private Data*/

	public:

		Mesh_PatchTemplate(const SurfType& theSurface)
			: SurfType(theSurface)
		{}

		//- Static functions and operators

		static std::shared_ptr<SurfType>
			ReParameterization
			(
				const SurfType& theSurface,
				const Standard_Real thsScale
			);

		static std::shared_ptr<SurfType>
			ReParameterization
			(
				const SurfType& theSurface,
				intgInfo& theInfo
			);
	};
}

#endif // !_Mesh_PatchTemplate_Header
