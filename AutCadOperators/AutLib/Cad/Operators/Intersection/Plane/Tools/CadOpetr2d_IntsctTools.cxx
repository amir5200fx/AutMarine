#include <CadOpetr2d_IntsctTools.hxx>

#include <Geom_ItemSort.hxx>
#include <CadOpetr2d_IntsctVertx.hxx>
#include <CadOpetr2d_IntsctEdge.hxx>
#include <CadOpetr2d_IntsctSegment.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean 
AutLib::CadOpetr2d_IntsctTools::IsIntersectionEntity
(
	const std::shared_ptr<Pln_Vertex>& theVertex
)
{
	return (Standard_Boolean)std::dynamic_pointer_cast
		<
		CadOpetr2d_IntsctVertx
		>(theVertex);
}

Standard_Boolean 
AutLib::CadOpetr2d_IntsctTools::IsIntersectionEntity
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	return (Standard_Boolean)std::dynamic_pointer_cast
		<
		CadOpetr2d_IntsctEdge
		>(theEdge);
}

void AutLib::CadOpetr2d_IntsctTools::Sort
(
	std::vector<std::shared_ptr<CadOpetr2d_IntsctEntity>>& theEntities
)
{
	Geom_ItemSort<std::shared_ptr<CadOpetr2d_IntsctEntity>> sort(&CadOpetr2d_IntsctEntity::IsLess);

	sort.Perform(theEntities);
}

void AutLib::CadOpetr2d_IntsctTools::SubdivideEdge
(
	const Pln_Edge& theEdge,
	const std::vector<std::shared_ptr<CadOpetr2d_IntsctEntity>>& theEntities, 
	std::vector<std::shared_ptr<CadOpetr2d_IntsctEdge>>& theSegments
)
{
	
	for (const auto& x : theEntities)
	{
		if (x->IsPoint())
		{
			
		}
		else
		{
			
		}
	}
}