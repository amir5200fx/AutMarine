#include <Pln_Cutter.hxx>

AutLib::Pln_Cutter::Pln_Cutter
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
	: Pln_Edge
	(
		theEdge->Index(), 
		theEdge->Name(), 
		theEdge->Vtx0(),
		theEdge->Vtx1(), 
		theEdge->Curve(),
		theEdge->Sense()
	)
	, theParent_(theEdge)
{
	ChangeMesh() = theEdge->Approx();
}