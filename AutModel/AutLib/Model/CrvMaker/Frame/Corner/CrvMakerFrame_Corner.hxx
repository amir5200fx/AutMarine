#pragma once
#ifndef _CrvMakerFrame_Corner_Header
#define _CrvMakerFrame_Corner_Header

#include <CrvMaker_Frame.hxx>

#include <memory>

namespace AutLib
{

	class CrvMakerFrame_Corner
		: public CrvMaker_Frame
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Pole> thePole0_;
		std::shared_ptr<CrvMaker_Pole> thePole1_;
		std::shared_ptr<CrvMaker_Pole> thePole2_;

	public:

		CrvMakerFrame_Corner
		(
			const std::shared_ptr<CrvMaker_Pole>& thePole0, 
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
		{}

		CrvMakerFrame_Corner
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
			, CrvMaker_Frame(theIndex)
		{}

		CrvMakerFrame_Corner
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<CrvMaker_Pole>& thePole0,
			const std::shared_ptr<CrvMaker_Pole>& thePole1,
			const std::shared_ptr<CrvMaker_Pole>& thePole2
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
			, thePole2_(thePole2)
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

		//- overide functions

		Standard_Boolean IsClosed() const override
		{
			return Standard_False;
		}

		Standard_Integer NbPoles() const override
		{
			return 3;
		}

		const std::shared_ptr<CrvMaker_Pole>&
			Pole
			(
				const Standard_Integer theIndex
			) const override;
	};
}

#endif // !_CrvMakerFrame_Corner_Header
