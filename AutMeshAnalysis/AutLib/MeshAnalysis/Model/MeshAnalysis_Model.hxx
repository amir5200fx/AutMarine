#pragma once
#ifndef _MeshAnalysis_Model_Header
#define _MeshAnalysis_Model_Header

#include <Global_Done.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <MeshAnalysis_Traits.hxx>
#include <MeshAnalysis_Model_Base.hxx>

#include <map>
#include <memory>

namespace AutLib
{

	// Forward Declarations
	template<class SurfPln>
	class Mesh_SingularDetection;

	template<class ModelTraits, class SizeFun, class CurveType, class SurfType = void>
	class MeshAnalysis_Model
		: public MeshAnalysis_Model_Base
		<
		SizeFun,
		typename meshAnalysis::model_type<CurveType, SurfType>::type, 
		CurveType
		>
		, public Global_Done
	{

		typedef MeshAnalysis_Model_Base
			<
			SizeFun,
			typename meshAnalysis::model_type<CurveType, SurfType>::type,
			CurveType
			> base;
		typedef typename SurfType::wireType wireType;
		typedef MeshAnalysis_Model_Info info;

		/*Private Data*/


		//- static functions and operators

		template<class SurfPln>
		static Standard_Boolean CheckRegulars
		(
			const Mesh_SingularDetection<SurfPln>& detection
		);

	public:

		MeshAnalysis_Model
		(
			const std::shared_ptr<info>& theInfo
		)
			: MeshAnalysis_Model_Base(theInfo)
		{}

		MeshAnalysis_Model
		(
			const std::shared_ptr<info>& theInfo,
			const std::shared_ptr<ModelType>& theModel
		)
			: MeshAnalysis_Model_Base(theInfo, theModel)
		{}

		void Perform();

		
	};

	template<class ModelTraits, class SizeFun, class CurveType>
	class MeshAnalysis_Model<ModelTraits, SizeFun, CurveType, void>
		: public MeshAnalysis_Model_Base
		<
		SizeFun,
		typename meshAnalysis::model_type<CurveType>::type,
		CurveType
		>
		, public Global_Done
	{

		/*Private Data*/
	};
}

#include <MeshAnalysis_ModelI.hxx>

#endif // !_MeshAnalysis_Model_Header
