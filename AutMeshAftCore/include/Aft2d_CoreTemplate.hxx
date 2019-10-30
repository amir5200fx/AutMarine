#pragma once
#ifndef _Aft2d_CoreTemplate_Header
#define _Aft2d_CoreTemplate_Header

#include <Aft_Core.hxx>
#include <Aft2d_FrontInfo.hxx>
#include <Aft2d_FrontGlobalData.hxx>

namespace AutLib
{

	template<class OptNodeAlg, class AftMetricPrcsr>
	using Aft2d_CoreTemplate = Aft_Core<OptNodeAlg, AftMetricPrcsr, Aft2d_FrontInfo, Aft2d_FrontGlobalData>;
}

#endif // !_Aft2d_CoreTemplate_Header
