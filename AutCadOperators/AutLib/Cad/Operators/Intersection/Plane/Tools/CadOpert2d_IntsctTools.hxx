#pragma once
#ifndef _CadOpert2d_IntsctTools_Header
#define _CadOpert2d_IntsctTools_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;
	class CadOpert2d_IntsctEntity;
	class CadOpert2d_IntsctEdge;

	class CadOpert2d_IntsctTools
	{

	public:

		static Standard_Boolean IsIntersectionEntity(const std::shared_ptr<Pln_Vertex>& theVertex);

		static Standard_Boolean IsIntersectionEntity(const std::shared_ptr<Pln_Edge>& theEdge);

		static void Sort(std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities);

		static void SubdivideEdge
		(
			const Pln_Edge& theEdge,
			const std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities,
			std::vector<std::shared_ptr<CadOpert2d_IntsctEdge>>& theSegments
		);
	};
}

#endif // !_CadOpert2d_IntsctTools_Header
