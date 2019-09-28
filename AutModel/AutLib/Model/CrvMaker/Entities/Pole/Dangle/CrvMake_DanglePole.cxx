#include <CrvMake_DanglePole.hxx>

#include <CrvMaker_TightPole.hxx>

std::shared_ptr<AutLib::CrvMaker_Pole> 
AutLib::CrvMake_DanglePole::Sum
(
	const std::shared_ptr<CrvMake_DanglePole>& theOther,
	const MergingInfo theAlg
) const
{
	Debug_Null_Pointer(theOther);
	auto pole = std::make_shared<CrvMaker_TightPole>();

	if (theAlg == First)
	{
		pole->SetCoord(Coord());
	}
	else if (theAlg == Second)
	{
		pole->SetCoord(theOther->Coord());
	}
	else
	{
		pole->SetCoord(MEAN(Coord(), theOther->Coord()));
	}

	return std::move(pole);
}

namespace AutLib
{

	std::shared_ptr<CrvMaker_Pole> 
		operator+
		(
			const std::shared_ptr<CrvMake_DanglePole>& thePole0,
			const std::shared_ptr<CrvMake_DanglePole>& thePole1
			)
	{
		Debug_Null_Pointer(thePole0);
		Debug_Null_Pointer(thePole1);

		auto pole = thePole0->Sum(thePole1, CrvMake_DanglePole::Middle);
		return std::move(pole);
	}
}