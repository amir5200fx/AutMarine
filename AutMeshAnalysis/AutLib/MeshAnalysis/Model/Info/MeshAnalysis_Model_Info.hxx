#pragma once
#ifndef _MeshAnalysis_Model_Info_Header
#define _MeshAnalysis_Model_Info_Header

#include <Standard_TypeDef.hxx>
#include <Global_Verbose.hxx>

#include <memory>
#include <map>

namespace AutLib
{

	// Forward Declarations
	class Geo_ApprxSurfMetricInfo;
	class Mesh_SingularDetection_Info;
	class CadRepair_NormalizeMetric_Info;
	class CadRepair_ParaPlaneAR_Info;

	class MeshAnalysis_Model_Info
		: public Global_Verbose
	{

		typedef Geo_ApprxSurfMetricInfo metricApprxInfo;
		typedef Mesh_SingularDetection_Info singularInfo;
		typedef CadRepair_NormalizeMetric_Info normInfo;
		typedef CadRepair_ParaPlaneAR_Info equalInfo;

		/*Private Data*/

		Standard_Real theMinSize_;

		std::shared_ptr<metricApprxInfo> theGlobalMetricApprxInfo_;
		std::shared_ptr<singularInfo> theGlobalSingularDetectInfo_;

		std::shared_ptr<normInfo> theNormInfo_;
		std::shared_ptr<equalInfo> theEqualInfo_;

		std::map<Standard_Integer, std::shared_ptr<metricApprxInfo>>
			theMetricApprxInfo_;
		std::map<Standard_Integer, std::shared_ptr<singularInfo>>
			theSinularDetectInfo_;

		Standard_Boolean OverrideMetricApprox_;
		Standard_Boolean OverrideSingDetect_;

	public:

		static const Standard_Real DEFAULT_MIN_SIZE;

		MeshAnalysis_Model_Info();

		Standard_Real MinSize() const
		{
			return theMinSize_;
		}

		Standard_Boolean OverrideMetricApproxInfo() const
		{
			return OverrideMetricApprox_;
		}

		Standard_Boolean OverrideSingDetectInfo() const
		{
			return OverrideSingDetect_;
		}

		const std::shared_ptr<metricApprxInfo>& 
			GlobalMetricApproxInfo() const
		{
			return theGlobalMetricApprxInfo_;
		}

		const std::shared_ptr<singularInfo>& 
			GlobalSingularDetectInfo() const
		{
			return theGlobalSingularDetectInfo_;
		}

		const std::shared_ptr<normInfo>& NormalizedMetricInfo() const
		{
			return theNormInfo_;
		}

		const std::shared_ptr<equalInfo>& EqualizerMetricInfo() const
		{
			return theEqualInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<metricApprxInfo>>&
			MetricApproxInfo() const
		{
			return theMetricApprxInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<singularInfo>>&
			SinglDetectInfo() const
		{
			return theSinularDetectInfo_;
		}

		void SetMinSize(const Standard_Real theSize)
		{
			theMinSize_ = theSize;
		}

		void SetToOverrideMetricApproxInfo(const Standard_Boolean Override)
		{
			OverrideMetricApprox_ = Override;
		}

		void SetToOverrideSingDetectInfo(const Standard_Boolean Override)
		{
			OverrideSingDetect_ = Override;
		}

		void OverrideGlobalMetricApproxInfo
		(
			const std::shared_ptr<metricApprxInfo>& theInfo
		)
		{
			theGlobalMetricApprxInfo_ = theInfo;
		}

		void OverrideGlobalSingDetectInfo
		(
			const std::shared_ptr<singularInfo>& theInfo
		)
		{
			theGlobalSingularDetectInfo_ = theInfo;
		}

		void OverrideNormalizedMetricInfo
		(
			const std::shared_ptr<normInfo>& theInfo
		)
		{
			theNormInfo_ = theInfo;
		}

		void OverrideEqualizerMetricInfo
		(
			const std::shared_ptr<equalInfo>& theInfo
		)
		{
			theEqualInfo_ = theInfo;
		}

		void OverrideMetricApproxInfo
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<metricApprxInfo>& theInfo
		);

		void OverrideSingDetectInfo
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<singularInfo>& theInfo
		);
	};
}

#endif // !_MeshAnalysis_Model_Info_Header
