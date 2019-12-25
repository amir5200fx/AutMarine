#pragma once
#ifndef _CadOpert2d_IntsctPair_Header
#define _CadOpert2d_IntsctPair_Header

#include <Global_AccessMethod.hxx>
#include <CadOpert2d_IntsctEntity.hxx>

namespace AutLib
{

	class CadOpert2d_IntsctPair
	{

		/*Private Data*/

		std::shared_ptr<CadOpert2d_IntsctEntity> theEntity0_;
		std::shared_ptr<CadOpert2d_IntsctEntity> theEntity1_;

	public:

		CadOpert2d_IntsctPair()
		{}

		//- Macros

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctEntity>, Entity0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctEntity>, Entity1)
	};
}

#endif // !_CadOpert2d_IntsctPair_Header
