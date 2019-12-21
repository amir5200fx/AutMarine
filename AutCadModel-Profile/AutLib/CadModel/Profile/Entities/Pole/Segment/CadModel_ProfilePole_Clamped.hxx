#pragma once
#ifndef _CadModel_ProfilePole_Clamped_Header
#define _CadModel_ProfilePole_Clamped_Header

#include <CadModel_ProfilePole.hxx>

namespace AutLib
{

	template<class PoleTraits>
	class CadModel_ProfilePole_Clamped
		: public CadModel_ProfilePole<PoleTraits>
	{

	public:

		typedef typename PoleTraits::segmentType segmentType;

	private:

		/*Private Data*/

		std::weak_ptr<segmentType> theBackward_;
		std::weak_ptr<segmentType> theForward_;

	public:

		CadModel_ProfilePole_Clamped()
		{}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<segmentType>, Backward)
			GLOBAL_ACCESS_SINGLE(std::weak_ptr<segmentType>, Forward)
	};
}

#endif // !_CadModel_ProfilePole_Clamped_Header
