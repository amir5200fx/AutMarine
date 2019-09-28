#include <CrvMakerFrame_PairedCorners.hxx>

#include <error.hxx>
#include <OSstream.hxx>

const std::shared_ptr<AutLib::CrvMaker_Pole>&
AutLib::CrvMakerFrame_PairedCorners::Pole
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, NbPoles() - 1))
	{
		FatalErrorIn("const std::shared_ptr<CrvMaker_Pole>& Pole(const Standard_Integer theIndex) const")
			<< "invalid Index" << endl
			<< abort(FatalError);
	}
	return (&thePole0_)[theIndex];
}