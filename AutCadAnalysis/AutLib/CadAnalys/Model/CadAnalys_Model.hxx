#pragma once
#ifndef _CadAnalys_Model_Header
#define _CadAnalys_Model_Header

#include <Global_Done.hxx>
#include <CadAnalys_Model_Base.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class ModelType>
	class CadAnalys_Model_Info;

	template<class ModelType, class SizeFun>
	class CadAnalys_Model
		: public CadAnalys_Model_Base<ModelType, SizeFun, typename ModelType::surfType>
	{

		typedef typename ModelType::surfType surfType;
		typedef typename surfType::curveType curveType;
		typedef typename surfType::wireType wireType;

		typedef CadAnalys_Model_Info<ModelType> info;

		typedef CadAnalys_Model_Base<ModelType, SizeFun, typename ModelType::surfType>
			base;

		/*Private Data*/

	public:

		CadAnalys_Model()
		{}

		void Perform();
	};
}

#include <CadAnalys_ModelI.hxx>

#endif // !_CadAnalys_Model_Header
