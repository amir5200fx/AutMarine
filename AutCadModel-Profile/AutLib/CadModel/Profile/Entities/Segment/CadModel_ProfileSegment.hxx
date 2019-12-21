#pragma once
#ifndef _CadModel_ProfileSegment_Header
#define _CadModel_ProfileSegment_Header

#include <CadModel_ProfileEntity.hxx>

namespace AutLib
{

	template<class SegmentTraits>
	class CadModel_ProfileSegment
		: public CadModel_ProfileEntity
	{

	public:

		typedef typename SegmentTraits::poleType poleType;

	private:

		/*Private Data*/

		std::shared_ptr<poleType> thePole0_;
		std::shared_ptr<poleType> thePole1_;

	public:

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<poleType>, Pole0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<poleType>, Pole1)
	};
}

#endif // !_CadModel_ProfileSegment_Header
