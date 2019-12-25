#include <CadOpert2d_IntsctTools.hxx>

#include <Geom_ItemSort.hxx>
#include <CadOpert2d_IntsctVertx.hxx>
#include <CadOpert2d_IntsctEdge.hxx>
#include <CadOpert2d_IntsctSegment.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean 
AutLib::CadOpert2d_IntsctTools::IsIntersectionEntity
(
	const std::shared_ptr<Pln_Vertex>& theVertex
)
{
	return (Standard_Boolean)std::dynamic_pointer_cast
		<
		CadOpert2d_IntsctVertx
		>(theVertex);
}

Standard_Boolean 
AutLib::CadOpert2d_IntsctTools::IsIntersectionEntity
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	return (Standard_Boolean)std::dynamic_pointer_cast
		<
		CadOpert2d_IntsctEdge
		>(theEdge);
}

void AutLib::CadOpert2d_IntsctTools::Sort
(
	std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities
)
{
	Geom_ItemSort<std::shared_ptr<CadOpert2d_IntsctEntity>> sort(&CadOpert2d_IntsctEntity::IsLess);

	sort.Perform(theEntities);
}

void AutLib::CadOpert2d_IntsctTools::SubdivideEdge
(
	const Pln_Edge& theEdge,
	const std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>& theEntities, 
	std::vector<std::shared_ptr<CadOpert2d_IntsctEdge>>& theSegments
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