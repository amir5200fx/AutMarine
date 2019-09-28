#pragma once
#ifndef _CrvMakerFrame_PairedCorners_Header
#define _CrvMakerFrame_PairedCorners_Header

#include <CrvMaker_Frame.hxx>

namespace AutLib
{

	class CrvMakerFrame_PairedCorners
		: public CrvMaker_Frame
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Pole> thePole0_;
		std::shared_ptr<CrvMaker_Pole> thePole1_;
		std::shared_ptr<CrvMaker_Pole> thePole2_;
		std::shared_ptr<CrvMaker_Pole> thePole3_;
		std::shared_ptr<CrvMaker_Pole> thePole4_;

	protected:

		CrvMakerFrame_PairedCorners
		(
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3,
			const std::shared_ptr<CrvMaker_Pole>& thePole4
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
			, thePole3_(thePole3)
			, thePole4_(thePole4)
		{}

		CrvMakerFrame_PairedCorners
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3,
			const std::shared_ptr<CrvMaker_Pole>& thePole4
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
			, thePole3_(thePole3)
			, thePole4_(thePole4)
			, CrvMaker_Frame(theIndex)
		{}

		CrvMakerFrame_PairedCorners
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3,
			const std::shared_ptr<CrvMaker_Pole>& thePole4
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
			, thePole3_(thePole3)
			, thePole4_(thePole4)
			, CrvMaker_Frame(theIndex, theName)
		{}

	public:


		const std::shared_ptr<CrvMaker_Pole>& Pole0() const
		{
			return thePole0_;
		}

		const std::shared_ptr<CrvMaker_Pole>& Pole1() const
		{
			return thePole1_;
		}

		const std::shared_ptr<CrvMaker_Pole>& Pole2() const
		{
			return thePole2_;
		}

		const std::shared_ptr<CrvMaker_Pole>& Pole3() const
		{
			return thePole3_;
		}

		const std::shared_ptr<CrvMaker_Pole>& Pole4() const
		{
			return thePole4_;
		}


		//- override functions

		Standard_Boolean IsClosed() const override
		{
			return Standard_False;
		}

		Standard_Integer NbPoles() const override
		{
			return 5;
		}

		const std::shared_ptr<CrvMaker_Pole>&
			Pole
			(
				const Standard_Integer theIndex
			) const override;
	};
}

#endif // !_CrvMakerFrame_PairedCorners_Header
