#include <Pln_CmpEdge.hxx>

#include <Pln_Edge.hxx>

void AutLib::Pln_CmpEdge::Reverse()
{
	auto& edges = theEdges_;

	for (auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->Reverse();
	}
	std::reverse(edges.begin(), edges.end());
}