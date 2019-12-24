#pragma once
#ifndef _CadOpetr2d_IntsctTools_Header
#define _CadOpetr2d_IntsctTools_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;
	class CadOpetr2d_IntsctEntity;
	class CadOpetr2d_IntsctEdge;

	class CadOpetr2d_IntsctTools
	{

	public:

		static Standard_Boolean IsIntersectionEntity(const std::shared_ptr<Pln_Vertex>& theVertex);

		static Standard_Boolean IsIntersectionEntity(const std::shared_ptr<Pln_Edge>& theEdge);

		static void Sort(std::vector<std::shared_ptr<CadOpetr2d_IntsctEntity>>& theEntities);

		static void SubdivideEdge
		(
			const Pln_Edge& theEdge,
			const std::vector<std::shared_ptr<CadOpetr2d_IntsctEntity>>& theEntities,
			std::vector<std::shared_ptr<CadOpetr2d_IntsctEdge>>& theSegments
		);
	};
}

#endif // !_CadOpetr2d_IntsctTools_Header
