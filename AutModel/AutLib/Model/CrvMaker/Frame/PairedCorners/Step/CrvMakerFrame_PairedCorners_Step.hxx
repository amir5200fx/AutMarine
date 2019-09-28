#pragma once
#ifndef _CrvMakerFrame_PairedCorners_Step_Header
#define _CrvMakerFrame_PairedCorners_Step_Header

#include <CrvMakerFrame_PairedCorners.hxx>

namespace AutLib
{

	class CrvMakerFrame_PairedCorners_Step
		: public CrvMakerFrame_PairedCorners
	{

		/*Private Data*/

	public:

		CrvMakerFrame_PairedCorners_Step
		(
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3,
			const std::shared_ptr<CrvMaker_Pole>& thePole4
		)
			: CrvMakerFrame_PairedCorners(thePole0, thePole1, thePole2, thePole3, thePole4)
		{}

		CrvMakerFrame_PairedCorners_Step
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3,
			const std::shared_ptr<CrvMaker_Pole>& thePole4
		)
			: CrvMakerFrame_PairedCorners(theIndex, thePole0, thePole1, thePole2, thePole3, thePole4)
		{}

		CrvMakerFrame_PairedCorners_Step
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3,
			const std::shared_ptr<CrvMaker_Pole>& thePole4
		)
			: CrvMakerFrame_PairedCorners(theIndex, theName, thePole0, thePole1, thePole2, thePole3, thePole4)
		{}
	};
}

#endif // !_CrvMakerFrame_PairedCorners_Step_Header
