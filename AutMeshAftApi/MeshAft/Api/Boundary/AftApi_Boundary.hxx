#pragma once
#ifndef _AftApi_Boundary_Header
#define _AftApi_Boundary_Header

#include <Global_Done.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <map>
#include <memory>

namespace AutLib
{

	template<class ModelType>
	class AftApi_Boundary
		: public Global_Done
		, public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/


	};
}

#endif // !_AftApi_Boundary_Header
