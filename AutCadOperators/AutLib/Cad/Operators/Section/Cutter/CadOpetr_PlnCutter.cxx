#include <CadOpetr_PlnCutter.hxx>

#include <error.hxx>
#include <OSstream.hxx>

#include <BRepAlgoAPI_Section.hxx>

void AutLib::CadOpetr_PlnCutter::Perform()
{
	BRepAlgoAPI_Section section;

	section.Init1(Target());
	section.Init2(Cutter());

	section.SetRunParallel(RunInParallel());

	section.Build();

	if (section.HasErrors())
	{
		FatalErrorIn("void Perform()")
			<< "the algorithm has been failed!"
			<< abort(FatalError);
	}

	ChangeShape() = section.Shape();
}