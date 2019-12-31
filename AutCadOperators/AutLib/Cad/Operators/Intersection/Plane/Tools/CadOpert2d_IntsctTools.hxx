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
	class Pln_Wire;
	class Pln_CmpEdge;
	class Cad2d_Plane;
	class CadOpert2d_IntsctEntity;
	class CadOpert2d_IntsctCmpEdge;
	class CadOpert2d_IntsctPair;
	class CadOpert2d_IntsctSubEdge;

	class CadOpert2d_IntsctTools
	{

	public:

		static Standard_Boolean IsIntersectionEntity(const std::shared_ptr<Pln_Vertex>& theVertex);

		static Standard_Boolean IsIntersectionEntity(const std::shared_ptr<Pln_Edge>& theEdge);

		static void Sort(std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities);

		static void SplitEntities
		(
			const std::vector<std::shared_ptr<CadOpert2d_IntsctPair>>& theEntities,
			std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities0,
			std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities1
		);

		static void SubdivideEdge
		(
			const Pln_Edge& theEdge,
			const std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities,
			std::vector<std::shared_ptr<CadOpert2d_IntsctSubEdge>>& theSegments
		);

		static std::shared_ptr<Pln_CmpEdge> SubdivideCmpEdge
		(
			const Pln_CmpEdge& theEdge,
			const std::map
			<
			Standard_Integer,
			std::shared_ptr<std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>>
			>& theEntities
		);

		static std::shared_ptr<Pln_Wire> SubdivideWire
		(
			const Pln_Wire& theWire, 
			const std::map
			<
			Standard_Integer, 
			std::shared_ptr<std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>>
			>& theEntities
		);

		static std::shared_ptr<Cad2d_Plane> SubdividePlane
		(
			const Cad2d_Plane& thePlane,
			const std::map
			<
			Standard_Integer,
			std::shared_ptr<std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>>
			>& theEntities
		);


	};
}

#endif // !_CadOpert2d_IntsctTools_Header
