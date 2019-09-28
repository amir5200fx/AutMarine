#include <CrvMakerFrame_Segment.hxx>

#include <error.hxx>
#include <OSstream.hxx>

const std::shared_ptr<AutLib::CrvMaker_Pole>& 
AutLib::CrvMakerFrame_Segment::Pole
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, NbPoles() - 1))
	{
		FatalErrorIn("const std::shared_ptr<AutLib::CrvMaker_Pole>& Pole(const Standard_Integer theIndex) const") << endl
			<< "Inavlid Index" << endl
			<< abort(FatalError);
	}
	return (&theP0_)[theIndex];
}