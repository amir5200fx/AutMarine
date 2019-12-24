#pragma once
#ifndef _CadOpetr2d_IntsctPair_Header
#define _CadOpetr2d_IntsctPair_Header

#include <Global_AccessMethod.hxx>
#include <CadOpetr2d_IntsctEntity.hxx>

namespace AutLib
{

	class CadOpetr2d_IntsctPair
	{

		/*Private Data*/

		std::shared_ptr<CadOpetr2d_IntsctEntity> theEntity0_;
		std::shared_ptr<CadOpetr2d_IntsctEntity> theEntity1_;

	public:

		CadOpetr2d_IntsctPair()
		{}

		//- Macros

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpetr2d_IntsctEntity>, Entity0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpetr2d_IntsctEntity>, Entity1)
	};
}

#endif // !_CadOpetr2d_IntsctPair_Header
