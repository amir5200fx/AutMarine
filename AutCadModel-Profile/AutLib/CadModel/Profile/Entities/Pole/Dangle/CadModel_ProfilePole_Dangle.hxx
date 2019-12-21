#pragma once
#ifndef _CadModel_ProfilePole_Dangle_Header
#define _CadModel_ProfilePole_Dangle_Header

#include <CadModel_ProfilePole.hxx>

namespace AutLib
{

	template<class PoleTraits>
	class CadModel_ProfilePole_Dangle
		: public CadModel_ProfilePole<PoleTraits>
	{

	public:

		typedef typename PoleTraits::segmentType segmentType;

	private:

		/*Private Data*/

		std::weak_ptr<segmentType> theSegment_;

	public:

		CadModel_ProfilePole_Dangle()
		{}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<segmentType>, Segment)
	};
}

#endif // !_CadModel_ProfilePole_Dangle_Header
