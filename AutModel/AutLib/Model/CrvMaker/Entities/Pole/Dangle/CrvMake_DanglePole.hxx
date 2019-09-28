#pragma once
#ifndef _CrvMake_DanglePole_Header
#define _CrvMake_DanglePole_Header

#include <CrvMaker_Pole.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	// Forward Declarations
	class CrvMaker_Segment;

	class CrvMake_DanglePole
		: public CrvMaker_Pole
	{

		/*Private Data*/

		std::weak_ptr<CrvMaker_Segment> theSegment_;

	public:

		enum MergingInfo {First, Second, Middle};

		CrvMake_DanglePole()
		{}

		CrvMake_DanglePole
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: CrvMaker_Pole(theIndex, theCoord)
		{}

		CrvMake_DanglePole
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: CrvMaker_Pole(theIndex, theName, theCoord)
		{}

		const std::weak_ptr<CrvMaker_Segment>& Segment() const
		{
			return theSegment_;
		}

		void SetSegment
		(
			const std::shared_ptr<CrvMaker_Segment>& theSegment
		)
		{
			theSegment_ = theSegment;
		}

		//- override functions

		Standard_Boolean IsDangle() const override
		{
			return Standard_True;
		}

		Standard_Integer NbSegments() const override
		{
			return 1;
		}

		const std::weak_ptr<CrvMaker_Segment>& 
			Segment
			(
				const Standard_Integer theIndex
			) const override
		{
			if (!theIndex)
			{
				FatalErrorIn("const std::weak_ptr<CrvMaker_Segment>& Segment(const Standard_Integer theIndex) const")
					<< "Invalid Index" << endl
					<< abort(FatalError);
			}
			return theSegment_;
		}

		std::shared_ptr<CrvMaker_Pole> 
			Sum
		(
			const std::shared_ptr<CrvMake_DanglePole>& theOther, 
			const MergingInfo theAlg
		) const;

		//- friend functions and operators

		friend std::shared_ptr<CrvMaker_Pole> 
			operator+
			(
				const std::shared_ptr<CrvMake_DanglePole>& thePole0, 
				const std::shared_ptr<CrvMake_DanglePole>& thePole1
				);
	};
}

#endif // !_CrvMake_DanglePole_Header
