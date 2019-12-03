#pragma once
#ifndef _CadAnalys_Model_Base_Header
#define _CadAnalys_Model_Base_Header

#include <Global_Done.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>

#include <map>
#include <memory>

namespace AutLib
{

	// Forward Declarations
	template<class ModelType>
	class CadAnalys_Model_Info;

	template<class ModelType, class SizeFun, class SubEntity>
	class CadAnalys_Model_Base
		: public Global_Done
		, public Global_Indexed
		, public Global_Named
	{

		typedef std::map<Standard_Integer, std::shared_ptr<SubEntity>>
			indexedEntityMap;
		typedef CadAnalys_Model_Info<ModelType> info;

		/*Private Data*/

		indexedEntityMap theRegulars_;
		indexedEntityMap theDefects_;

		indexedEntityMap theDeepSingulars_;
		indexedEntityMap theCommonSingulars_;

		std::shared_ptr<SizeFun> theSizeFunction_;
		std::shared_ptr<ModelType> theModel_;
		std::shared_ptr<info> theInfo_;

	protected:

		CadAnalys_Model_Base
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		CadAnalys_Model_Base
		(
			const std::shared_ptr<info>& theInfo,
			const std::shared_ptr<ModelType>& theModel
		)
			: theInfo_(theInfo)
			, theModel_(theModel)
		{}

		indexedEntityMap& ChangeRegulars()
		{
			return theRegulars_;
		}

		indexedEntityMap& ChangeDefects()
		{
			return theDefects_;
		}

		indexedEntityMap& ChangeDeepSingulars()
		{
			return theDeepSingulars_;
		}

		indexedEntityMap& ChangeCommonSingulars()
		{
			return theCommonSingulars_;
		}

	public:

		Standard_Integer NbRegulars() const
		{
			return (Standard_Integer)theRegulars_.size();
		}

		Standard_Integer NbDefects() const
		{
			return (Standard_Integer)theDefects_.size();
		}

		Standard_Integer NbDeepSingularities() const
		{
			return (Standard_Integer)theDeepSingulars_.size();
		}

		Standard_Integer NbCommonSingularities() const
		{
			return (Standard_Integer)theCommonSingulars_.size();
		}

		const std::shared_ptr<SizeFun>& SizeFunction() const
		{
			return theSizeFunction_;
		}

		const std::shared_ptr<ModelType>& Model() const
		{
			return theModel_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const indexedEntityMap& Regulars() const
		{
			return theRegulars_;
		}

		indexedEntityMap& Regulars()
		{
			return theRegulars_;
		}

		const indexedEntityMap& Defects() const
		{
			return theDefects_;
		}

		indexedEntityMap& Defects()
		{
			return theDefects_;
		}

		const indexedEntityMap& DeepSingulars() const
		{
			return theDeepSingulars_;
		}

		indexedEntityMap& DeepSingulars()
		{
			return theDeepSingulars_;
		}

		const indexedEntityMap& CommonSingulars() const
		{
			return theCommonSingulars_;
		}

		indexedEntityMap& CommonSingulars()
		{
			return theCommonSingulars_;
		}

		void LoadSizeFunction(const std::shared_ptr<SizeFun>& theSizeFun)
		{
			theSizeFunction_ = theSizeFun;
		}

		void LoadModel(const std::shared_ptr<ModelType>& theModel)
		{
			theModel_ = theModel;
		}

		void LoadInfo(const std::shared_ptr<info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#endif // !_CadAnalys_Model_Base_Header
