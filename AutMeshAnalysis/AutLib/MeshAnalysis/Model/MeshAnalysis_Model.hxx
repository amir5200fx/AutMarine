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
		typename MeshAnalysis_Model<CurveType, SurfType>::type, 
		CurveType
		>
	{

		typedef MeshAnalysis_Model_Base
			<
			SizeFun,
			typename MeshAnalysis_Model<CurveType, SurfType>::type,
			CurveType
			> base;
		typedef typename SurfType::wireType wireType;

		/*Private Data*/


		//- static functions and operators

		template<class SurfPln>
		static Standard_Boolean CheckRegulars
		(
			const Mesh_SingularDetection<SurfPln>& detection
		);

	public:

		void Perform();

		
	};

	template<class ModelTraits, class SizeFun, class CurveType>
	class MeshAnalysis_Model<ModelTraits, SizeFun, CurveType, void>
		: public Global_Done
		, public Global_Indexed
		, public Global_Named
	{

		typedef std::map<Standard_Integer, std::shared_ptr<CurveType>>
			indexedCurveMap;

		/*Private Data*/

		indexedCurveMap theRegulars_;
		indexedCurveMap theDefects_;

		indexedCurveMap theDeepSingulars_;
	};
}

#include <MeshAnalysis_ModelI.hxx>

#endif // !_MeshAnalysis_Model_Header
