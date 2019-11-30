#include <CadOpts_PlnIntsct_Edge.hxx>

#include <Global_Macros.hxx>
#include <CadOpts_PlnIntsct_Vertex.hxx>

void AutLib::CadOpts_PlnIntsct_Edge::Insert(const std::shared_ptr<Pln_Edge>& theEdge)
{
	Pln_CmpEdge::Insert(theEdge);
}

Standard_Boolean 
AutLib::CadOpts_PlnIntsct_Edge::IsForward
(
	const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& theVertex
)
{
	if (theVertex IS_EQUAL Vtx0())
	{
		return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean 
AutLib::CadOpts_PlnIntsct_Edge::IsBackward
(
	const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& theVertex
)
{
	if (theVertex IS_EQUAL Vtx1())
	{
		return Standard_True;
	}
	return Standard_False;
}