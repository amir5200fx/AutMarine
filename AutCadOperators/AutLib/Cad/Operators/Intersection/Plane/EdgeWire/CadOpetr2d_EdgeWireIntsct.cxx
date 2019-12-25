#include <CadOpetr2d_EdgeWireIntsct.hxx>

#include <Global_Macros.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void AutLib::CadOpetr2d_EdgeWireIntsct::Perform()
{
	if (NOT Edge())
	{
		FatalErrorIn("void Perform()")
			<< "no edge has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Wire())
	{
		FatalErrorIn("void Perform()")
			<< "no wire has been loaded!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Edge()->Curve());
}