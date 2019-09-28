#pragma once
#ifndef _CrvMakerFrame_Segment_Header
#define _CrvMakerFrame_Segment_Header

#include <CrvMaker_Frame.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	class CrvMakerFrame_Segment
		: public CrvMaker_Frame
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Pole> theP0_;
		std::shared_ptr<CrvMaker_Pole> theP1_;

	public:

		CrvMakerFrame_Segment
		(
			const std::shared_ptr<CrvMaker_Pole>& theP0,
			const std::shared_ptr<CrvMaker_Pole>& theP1
		)
			: theP0_(theP0)
			, theP1_(theP1)
		{}

		CrvMakerFrame_Segment
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<CrvMaker_Pole>& theP0,
			const std::shared_ptr<CrvMaker_Pole>& theP1
		)
			: theP0_(theP0)
			, theP1_(theP1)
			, CrvMaker_Frame(theIndex)
		{}

		CrvMakerFrame_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<CrvMaker_Pole>& theP0,
			const std::shared_ptr<CrvMaker_Pole>& theP1
		)
			: theP0_(theP0)
			, theP1_(theP1)
			, CrvMaker_Frame(theIndex, theName)
		{}


		const std::shared_ptr<CrvMaker_Pole>& Pole0() const
		{
			return theP0_;
		}

		const std::shared_ptr<CrvMaker_Pole>& Pole1() const
		{
			return theP1_;
		}

		//- override functions 

		Standard_Boolean IsClosed() const override
		{
			return Standard_False;
		}

		Standard_Integer NbPoles() const override
		{
			return 2;
		}

		const std::shared_ptr<CrvMaker_Pole>&
			Pole
			(
				const Standard_Integer theIndex
			) const override;

	};
}

#endif // !_CrvMakerFrame_Segment_Header
