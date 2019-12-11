#include <CadAnalys_Edge.hxx>

#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <BRep_Tool.hxx>

void AutLib::CadAnalys_Edge::Perform()
{
	if (Edge().IsNull())
	{
		FatalErrorIn("void Perform()")
			<< " no edge has been loaded!" << endl
			<< abort(FatalError);
	}

	SameParameter_ = BRep_Tool::SameParameter(Edge());
	SameRange_ = BRep_Tool::SameRange(Edge());
	Geometric_ = NOT BRep_Tool::IsGeometric(Edge());
	Degenerated_ = BRep_Tool::Degenerated(Edge());

	theTolerance_ = BRep_Tool::Tolerance(Edge());

	Change_IsDone() = Standard_True;
}