#pragma once
#ifndef _AftApi_BndCurves_Header
#define _AftApi_BndCurves_Header

#include <Global_Done.hxx>
#include <Global_Named.hxx>
#include <Global_Verbose.hxx>

#include <memory>
#include <map>

namespace AutLib
{

	template<class ModelType>
	class AftApi_BndCurves
		: public Global_Done
		, public Global_Named
		, public Global_Verbose
	{

		typedef typename ModelType::parCurveType parCurveType;

		typedef std::map<Standard_Integer, std::shared_ptr<parCurveType>>
			indexed
		/*Private Data*/


	};
}

#endif // !_AftApi_BndCurves_Header
