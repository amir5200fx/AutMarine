#pragma once
#ifndef _CadAnalys_Model_Header
#define _CadAnalys_Model_Header

#include <Global_Done.hxx>
#include <CadAnalys_Model_Base.hxx>
#include <CadAnalys_Patch.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class ModelType>
	class CadAnalys_Model_Info;

	template<class SurfPln>
	class CadSingularity_Detection;

	template<class ModelType, class SizeFun>
	class CadAnalys_Model
		: public CadAnalys_Model_Base<ModelType, SizeFun, CadAnalys_Patch<typename ModelType::surfType>>
	{

		typedef typename ModelType::surfType surfType;
		typedef typename surfType::curveType curveType;
		typedef typename surfType::wireType wireType;

		typedef CadAnalys_Model_Info<ModelType> info;

		typedef CadAnalys_Model_Base<ModelType, SizeFun, typename ModelType::surfType>
			base;

		/*Private Data*/

		//- static functions and operators

		template<class SurfPln>
		static Standard_Boolean CheckRegulars
		(
			const CadSingularity_Detection<SurfPln>& detection
		);


	public:

		CadAnalys_Model()
		{}

		void Perform();
	};
}

#include <CadAnalys_ModelI.hxx>

#endif // !_CadAnalys_Model_Header
