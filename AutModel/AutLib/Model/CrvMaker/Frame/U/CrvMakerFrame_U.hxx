#pragma once
#ifndef _CrvMakerFrame_U_Header
#define _CrvMakerFrame_U_Header

#include <CrvMaker_Frame.hxx>

namespace AutLib
{

	class CrvMakerFrame_U
		: public CrvMaker_Frame
	{

		/*private Data*/

		std::shared_ptr<CrvMaker_Pole> thePole0_;
		std::shared_ptr<CrvMaker_Pole> thePole1_;
		std::shared_ptr<CrvMaker_Pole> thePole2_;
		std::shared_ptr<CrvMaker_Pole> thePole3_;

	public:

		CrvMakerFrame_U
		(
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
			, thePole3_(thePole3)
		{}

		CrvMakerFrame_U
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
			, thePole3_(thePole3)
			, CrvMaker_Frame(theIndex)
		{}

		CrvMakerFrame_U
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2,
			const std::shared_ptr<CrvMaker_Pole>& thePole3
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
			, thePole3_(thePole3)
			, CrvMaker_Frame(theIndex, theName)
		{}

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


		//- override functions

		Standard_Boolean IsClosed() const override
		{
			return Standard_False;
		}

		Standard_Integer NbPoles() const override
		{
			return 4;
		}

		const std::shared_ptr<CrvMaker_Pole>&
			Pole
			(
				const Standard_Integer theIndex
			) const override;
	};
}

#endif // !_CrvMakerFrame_U_Header
