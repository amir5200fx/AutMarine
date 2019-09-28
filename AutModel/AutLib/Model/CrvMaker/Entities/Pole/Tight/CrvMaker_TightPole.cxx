#include <CrvMaker_TightPole.hxx>

#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>

const std::weak_ptr<AutLib::CrvMaker_Segment>& 
AutLib::CrvMaker_TightPole::Segment
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, 1))
	{
		FatalErrorIn("const std::weak_ptr<CrvMaker_Segment>& Segment(const Standard_Integer theIndex) const")
			<< "Invalid Index" << endl
			<< abort(FatalError);
	}
	return (&theFormer_)[theIndex];
}