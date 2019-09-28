#pragma once
#ifndef _CrvMake_TightPole_Header
#define _CrvMake_TightPole_Header

#include <CrvMaker_Pole.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CrvMaker_Segment;

	class CrvMaker_TightPole
		: public CrvMaker_Pole
	{

		/*Private Data*/

		std::weak_ptr<CrvMaker_Segment> theFormer_;
		std::weak_ptr<CrvMaker_Segment> theLatter_;

	public:

		CrvMaker_TightPole()
		{}

		CrvMaker_TightPole
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: CrvMaker_Pole(theIndex, theCoord)
		{}

		CrvMaker_TightPole
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: CrvMaker_Pole(theIndex, theName, theCoord)
		{}

		const std::weak_ptr<CrvMaker_Segment>& Former() const
		{
			return theFormer_;
		}

		const std::weak_ptr<CrvMaker_Segment>& Latter() const
		{
			return theLatter_;
		}

		void SetFormer(const std::shared_ptr<CrvMaker_Segment>& theSegment)
		{
			theFormer_ = theSegment;
		}

		void SetLatter(const std::shared_ptr<CrvMaker_Segment>& theSegment)
		{
			theLatter_ = theSegment;
		}

		//- virtual functions and operators

		virtual Standard_Boolean IsTerminal() const
		{
			return Standard_False;
		}

		//- override functions

		Standard_Boolean IsTight() const override
		{
			return Standard_True;
		}

		Standard_Integer NbSegments() const override
		{
			return 2;
		}

		const std::weak_ptr<CrvMaker_Segment>&
			Segment
			(
				const Standard_Integer theIndex
			) const override;
	};
}

#endif // !_CrvMake_TightPole_Header
