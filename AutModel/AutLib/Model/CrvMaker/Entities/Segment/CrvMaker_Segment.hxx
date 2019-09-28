#pragma once
#ifndef _CrvMaker_Segment_Header
#define _CrvMaker_Segment_Header

#include <CrvMaker_Entity.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CrvMaker_Pole;

	class CrvMaker_Segment
		: public CrvMaker_Entity
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Pole> theFirst_;
		std::shared_ptr<CrvMaker_Pole> theLast_;

	public:

		CrvMaker_Segment()
		{}

		CrvMaker_Segment(const Standard_Integer theIndex)
			: CrvMaker_Entity(theIndex)
		{}

		CrvMaker_Segment(const Standard_Integer theIndex, const word& theName)
			: CrvMaker_Entity(theIndex, theName)
		{}

		CrvMaker_Segment
		(
			const std::shared_ptr<CrvMaker_Pole>& theFirst,
			const std::shared_ptr<CrvMaker_Pole>& theLast
		)
			: theFirst_(theFirst)
			, theLast_(theLast)
		{}

		CrvMaker_Segment
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<CrvMaker_Pole>& theFirst,
			const std::shared_ptr<CrvMaker_Pole>& theLast
		)
			: theFirst_(theFirst)
			, theLast_(theLast)
			, CrvMaker_Entity(theIndex)
		{}

		CrvMaker_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<CrvMaker_Pole>& theFirst,
			const std::shared_ptr<CrvMaker_Pole>& theLast
		)
			: theFirst_(theFirst)
			, theLast_(theLast)
			, CrvMaker_Entity(theIndex, theName)
		{}


		const std::shared_ptr<CrvMaker_Pole>& First() const
		{
			return theFirst_;
		}

		const std::shared_ptr<CrvMaker_Pole>& Last() const
		{
			return theLast_;
		}

		void SetFirst(const std::shared_ptr<CrvMaker_Pole>& theFirst)
		{
			theFirst_ = theFirst;
		}

		void SetLast(const std::shared_ptr<CrvMaker_Pole>& theLast)
		{
			theLast_ = theLast;
		}
	};
}

#endif // !_CrvMaker_Segment_Header
