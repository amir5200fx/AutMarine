#pragma once
#include <CadAnalys_BadARPatch.hxx>
#include <CadAnalys_DefectPatch_OpenWire.hxx>
#include <CadAnalys_DefectPatch_OrderWire.hxx>

#include <CadRepair_DefectPatch_AR.hxx>
#include <CadRepair_DefectPatch_OrderWire.hxx>
#include <CadRepair_DefectPatch_OpenWire.hxx>
#include <CadRepair_DefectPatch_IntersectWire.hxx>
#include <CadRepair_DefectPatch_Metric.hxx>
#include <CadRepair_ApproxSurfMetric.hxx>
#include <CadRepair_ColoringSurfMetric.hxx>
#include <CadRepair_NormalizeMetric.hxx>

namespace AutLib
{

	template<class ModelType, class SizeFun>
	void CadAnalys_Model<ModelType, SizeFun>::Perform()
	{
		if (NOT base::Model())
		{
			FatalErrorIn("void Perform()")
				<< "the model has not been loaded!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(base::Info());

		const auto& model = *base::Model();
		const auto& surfaces = model.Surfaces();

		const auto verbose = base::Info()->Verbose();
		for (const auto& x : surfaces)
		{
			Debug_Null_Pointer(x);

			if (verbose)
			{
				GET_MESSAGE << " checking surface nb. " << x->Index() << ";";
				SEND_INFO;

				GET_MESSAGE << " surface's name: " << x->Name() << ";";
				SEND_INFO;
			}
			
			if (verbose)
			{
				GET_MESSAGE << "  checking plane balancing...";
				SEND_INFO;
			}

			auto ar = CadRepair_DefectPatch_AR<surfType>::CalcMaxAR(*x);
			if (ar > base::Info()->MaxAR())
			{
				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared
						<
						CadRepair_DefectPatch_AR<surfType>>(x->Index(), x)));

				continue;
			}

			std::vector<std::shared_ptr<wireType>> wires;
			if (CadRepair_DefectPatch_OrderWire<surfType>::Check(*x, wires))
			{

				if (verbose)
				{
					GET_MESSAGE << " defect wire has been detected: WIRE ORDER";
					SEND_WARNING;
				}

				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared
						<
						CadRepair_DefectPatch_OrderWire<surfType>>(x->Index(), x, wires)));

				continue;
			}

			if (CadRepair_DefectPatch_OpenWire<surfType>::Check(*x, base::Info()->OpenWireTolerance()))
			{

				if (verbose)
				{
					GET_MESSAGE << " defect wire has been detected: OPENNED WIRE";
					SEND_WARNING;
				}

				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared
						<
						CadRepair_DefectPatch_OpenWire<surfType>>(x->Index(), x, wires)));

				continue;
			}

			std::shared_ptr<wireType> outerWire;
			std::shared_ptr<wireType> innerWire;
			if (CadRepair_DefectPatch_IntersectWire<surfType>::Check(*x, outerWire, innerWire, base::Info()->InterstWireTolerance()))
			{

				if (verbose)
				{
					GET_MESSAGE << " defect wire has been detected: INTERSECTED WIRES";
					SEND_WARNING;
				}

				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared
						<
						CadRepair_DefectPatch_IntersectWire<surfType>>(x->Index(), x, outerWire, innerWire)));

				continue;
			}

			auto approxInfo = base::Info()->GlobalMetricApproxInfo();
			Debug_Null_Pointer(approxInfo);

			if (base::Info()->OverrideGlobalMetricApproxInfo())
			{
				const auto& appMap = base::Info()->MetricApproxInfo();
				auto iter = appMap.find(x->Index());

				if (iter NOT_EQUAL appMap.end())
				{
					approxInfo = iter->second;
				}
			}

			if (verbose)
			{
				GET_MESSAGE << " - Overriding metric approximation settings? " << (base::Info()->OverrideMetricApproxInfo() ? "YES" : "NO");
				SEND_INFO;

				GET_MESSAGE << "  - Min Level: " << approxInfo->MinLevel();
				SEND_INFO;
				GET_MESSAGE << "  - Max Level: " << approxInfo->MaxLevel();
				SEND_INFO;
				GET_MESSAGE << "  - Tolerance: " << approxInfo->Tolerance();
				SEND_INFO;
				GET_MESSAGE << "  - Degeneracy: " << approxInfo->Degeneracy();
				SEND_INFO;
			}

			auto approx =
				std::make_shared<CadRepair_ApproxSurfMetric>
				(
					x->Geometry(),
					x->BoundingBox(), approxInfo);
			Debug_Null_Pointer(approx);

			approx->Perform();
			Debug_If_Condition_Message
			(
				NOT approx->IsDone(),
				"the Geo_ApprxSurfaceMetric has not been performed!");

			if (verbose)
			{
				GET_MESSAGE << "  making an approximation of the surface metric is done!";
				SEND_INFO;
				GET_MESSAGE << "  checking for normalizing the metric...";
				SEND_INFO;
			}

			Debug_Null_Pointer(base::Info()->NormalizedMetricInfo());

			if (approx->MaxDet() > base::Info()->NormalizedMetricInfo()->MaxDet())
			{

				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared
						<
						CadRepair_DefectPatch_Metric<surfType>>(x->Index(), x, approx)));

				continue;
			}
		}

	}
}