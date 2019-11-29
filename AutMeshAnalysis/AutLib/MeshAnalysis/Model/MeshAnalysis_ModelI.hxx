#pragma once
#include <Global_Message.hxx>
#include <CadAnalys_ApprxSurfMetric.hxx>
#include <CadAnalys_ColoringSurfMetric.hxx>
#include <Mesh_DefectPatch_UnBalancedAR.hxx>
#include <Mesh_DefectPatch_OrderWire.hxx>
#include <Mesh_DefectPatch_OpenWire.hxx>
#include <Mesh_DefectPatch_IntersectWire.hxx>
#include <Mesh_SingularHorizon.hxx>
#include <Mesh_PatchTemplate.hxx>
#include <Mesh_SingularDetection.hxx>
#include <Mesh_SingularTraits.hxx>
#include <Mesh_SingularPatch_Regular.hxx>
#include <Mesh_SingularPatch_Deep.hxx>
#include <CadRepair_ParaPlaneAR.hxx>
#include <CadRepair_NormalizeMetric.hxx>
#include <CadAnalys_ApprxSurfMetricInfo.hxx>
#include <CadRepair_ParaPlaneAR_Info.hxx>
#include <CadRepair_NormalizeMetric_Info.hxx>
#include <Mesh_SingularDetection_Info.hxx>
#include <SingularZone_Pole_WholeSide.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class ModelTraits, class SizeFun, class CurveType, class SurfType>
	template<class SurfPln>
	Standard_Boolean MeshAnalysis_Model<ModelTraits, SizeFun, CurveType, SurfType>::CheckRegulars
	(
		const Mesh_SingularDetection<SurfPln>& detection
	)
	{
		if (NOT detection.NbZones())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the singular surface has no singularity zone!" << endl
				<< abort(FatalError);
		}

		const auto& zones = detection.Zones();
		for (const auto& x : zones)
		{
			Debug_Null_Pointer(x);
			if (NOT std::dynamic_pointer_cast<SingularZone_Pole_WholeSide<SurfPln>>(x))
			{
				return Standard_True;
			}
		}
		return Standard_False;
	}

	template<class ModelTraits, class SizeFun, class CurveType, class SurfType>
	void MeshAnalysis_Model<ModelTraits, SizeFun, CurveType, SurfType>::Perform()
	{
		if (NOT base::Model())
		{
			FatalErrorIn("void MeshAnalysis_Model<CurveType, SurfType>::Perform()") << endl
				<< "Found no model" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(base::Info());

		const auto& sizeMap = base::SizeFunction();
		const auto& model = *base::Model();

		const auto& surfaces = model.Surfaces();

		auto normSurfMetric =
			std::make_shared<CadRepair_NormalizeMetric<SurfType>>(base::Info()->NormalizedMetricInfo());
		
		const auto verbose = base::Info()->Verbose();
		for (const auto& isurface : surfaces)
		{

			if (verbose)
			{
				GET_MESSAGE << " checking surface nb. " << x->Index() << ";";
				SEND_INFO;

				GET_MESSAGE << " surface's name: " << x->Name() << ";";
				SEND_INFO;
			}

			auto x = isurface;
			Debug_Null_Pointer(x);

			if (verbose)
			{
				GET_MESSAGE << "  checking plane balancing...";
				SEND_INFO;
			}

			auto planeEqual = std::make_shared<CadRepair_ParaPlaneAR<SurfType>>
				(
					base::Info()->EqualizerMetricInfo()
					);
			Debug_Null_Pointer(planeEqual);

			planeEqual->LoadSurface(x);


			//- put the surface on the defects as unbalancing plane one if the AR of the plane
			// is bigger than the criterion
			try
			{
				planeEqual->Perform();

				Debug_If_Condition_Message(NOT planeEqual->IsDone(), " the metric equalizer has not been performed!");

				if (planeEqual->Applied())
				{
					x = planeEqual->Modified();
				}

				if (verbose)
				{
					GET_MESSAGE << " Balancing the plane has been applied successfully!";
					SEND_INFO;
				}
			}
			catch (const std::exception&)
			{

				//- it will throw an exception if the program has not been permitted 
				// to deal with the unbalancing
				if (verbose)
				{
					if (base::Info()->EqualizerMetricInfo()->ToApply())
					{
						GET_MESSAGE << " Unable to deal with the plane unbalancing...";
						SEND_WARNING;
					}
					else
					{
						GET_MESSAGE << " Dealing with plane unbalancing not permitted!";
						SEND_WARNING;
					}
				}

				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared<
						Mesh_DefectPatch_UnBalancedAR
						<
						SurfType, 
						typename ModelTraits::sizeFun, 
						typename ModelTraits::metricFun
						>>(x)));

				continue;
			}
			
			// checking the surface for having a wire ordering issue
			std::vector<std::shared_ptr<wireType>> wires;
			if (Mesh_DefectPatch_OrderWire<SurfType>::Check(*x, wires))
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
						std::make_shared<
						Mesh_DefectPatch_OrderWire
						<
						SurfType,
						typename ModelTraits::sizeFun,
						typename ModelTraits::metricFun
						>>(x, wires)));

				continue;
			}
			
			if (Mesh_DefectPatch_OpenWire<SurfType>::Check(*x, base::Info()->OpenWireTolerance()))
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
						std::make_shared<
						Mesh_DefectPatch_OpenWire
						<
						SurfType,
						typename ModelTraits::sizeFun,
						typename ModelTraits::metricFun
						>>(x, wires)));

				continue;
			}
			
			std::shared_ptr<wireType> outerWire;
			std::shared_ptr<wireType> innerWire;
			if (Mesh_DefectPatch_IntersectWire<SurfType>::Check(*x, outerWire, innerWire, base::Info()->InterstWireTolerance()))
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
						std::make_shared<
						Mesh_DefectPatch_OpenWire
						<
						SurfType,
						typename ModelTraits::sizeFun,
						typename ModelTraits::metricFun
						>>(x, outerWire, innerWire)));

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
				std::make_shared<CadAnalys_ApprxSurfMetric>
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

			auto normalizedMetric = 
				std::make_shared<CadRepair_NormalizeMetric>
				(
					base::Info()->NormalizedMetricInfo()
					);
			Debug_Null_Pointer(normalizedMetric);

			normalizedMetric->LoadMetric(approx);
			normalizedMetric->LoadSurface(x);

			try
			{
				normalizedMetric->Perform();
				Debug_If_Condition_Message
				(
					NOT normalizedMetric->IsDone(),
					"the normalizing metric surface has not been performed!");

				if (normalizedMetric->Applied())
				{
					x = normalizedMetric->Normalized();

					if (verbose)
					{
						GET_MESSAGE << "  remaking an approximation of the surface metric!";
						SEND_INFO;
					}

					auto approx =
						std::make_shared<CadAnalys_ApprxSurfMetric>
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
						GET_MESSAGE << "  remaking an approximation of the surface metric is done!";
						SEND_INFO;
						GET_MESSAGE << "  maximum metric determinant of the surface: " << approx->MaxDet();
						SEND_INFO;
					}
				}
			}
			catch (const std::exception&)
			{

				if (verbose)
				{
					if (approxInfo->ToApply())
					{
						GET_MESSAGE << " Unable to deal with the bad metrics...";
						SEND_WARNING;
					}
					else
					{
						GET_MESSAGE << " Dealing with bad metrics is not permitted!";
						SEND_WARNING;
					}
				}

				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared<
						Mesh_DefectPatch_BadMetric
						<
						SurfType,
						typename ModelTraits::sizeFun,
						typename ModelTraits::metricFun
						>>(x)));

				continue;
			}

			if (verbose)
			{
				GET_MESSAGE << "  Proceeding to detect the horizons of singularities...";
				SEND_INFO;
			}

			auto horizons =
				std::make_shared<Mesh_SingularHorizon>(x->Index(), approx);

			horizons->Perform();
			Debug_If_Condition_Message
			(
				NOT horizons->IsDone(),
				"the Mesh_SingularHorizon has not been performed!");

			if (verbose)
			{
				GET_MESSAGE << "  detecting of horizons has been completed!";
				SEND_INFO;
				GET_MESSAGE << "  - Has been any horizons detected? " << (horizons->HasHorizon() ? "YES" : "NO");
				SEND_INFO;

				if (horizons->HasHorizon())
				{
					GET_MESSAGE << "  - Nb. of horizons: " << horizons->NbHorizons();
					SEND_INFO;
				}
			}

			if (NOT horizons->HasHorizon())
			{

				if (verbose)
				{
					GET_MESSAGE << "  ****registering the surface as a perfection one!****";
					SEND_INFO;

					GET_MESSAGE << "  continue...";
					SEND_INFO;
				}

				base::ChangeRegulars().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared
						<
						Mesh_PatchTemplate
						<
						SurfType,
						typename ModelTraits::sizeFun,
						typename ModelTraits::metricFun
						>>(x)));

				continue;
			}
			else if (horizons->HasHorizon())
			{
				if (verbose)
				{
					GET_MESSAGE << "  Coloring algorithm has been called!";
					SEND_INFO;
				}

				auto colors =
					std::make_shared<CadAnalys_ColoringSurfMetric>(approx);

				colors->Perform();
				Debug_If_Condition_Message(NOT colors->IsDone(), "the color algorithm has not been performed");

				if (verbose)
				{
					GET_MESSAGE << "  Coloring the regions has been finished";
					SEND_INFO;

					GET_MESSAGE << "  Proceeding to detect the type of singularities...";
					SEND_INFO;
				}

				Debug_Null_Pointer(base::Info()->GlobalSingularDetectInfo());

				auto typeDetecInfo = base::Info()->GlobalSingularDetectInfo();
				if (base::Info()->OverrideGlobalSingDetectInfo())
				{
					const auto& typeMap = base::Info()->SinglDetectInfo();
					auto iter = typeMap.find(x->Index());

					if (iter IS_EQUAL typeMap.end())
					{
						typeDetecInfo = iter->second;
					}
				}

				if (verbose)
				{
					GET_MESSAGE << "  - Overriding settings? " << (Info()->OverrideSingDetectInfo() ? "YES" : "NO");
					SEND_INFO;

					GET_MESSAGE << "  - Nb. of iterations: " << typeDetecInfo->NbIters();
					SEND_INFO;

					GET_MESSAGE << "  - Omega: " << typeDetecInfo->Omega();
					SEND_INFO;
				}

				auto detection =
					std::make_shared<Mesh_SingularDetection<typename singularLib::mesh_surface_plane<SurfType>::type>>
					(
						horizons, colors,
						sizeMap, typeDetecInfo);

				detection->Perform(os);
				Debug_If_Condition_Message(NOT detection->IsDone(), "the type detection algorithm has not been performed");

				if (verbose)
				{
					GET_MESSAGE << "  type detection has been performed successfully! ";
					SEND_INFO;
				}

				if (CheckRegulars(*detection))
				{
					base::ChangeDeepSingulars().insert
					(
						std::make_pair(x->Index(),
							std::make_shared
							<Mesh_SingularPatch_Deep
							<
							SurfType,
							typename ModelTraits::sizeFun,
							typename ModelTraits::metricFun>>
							(x, detection)));

					continue;
				}
				else
				{
					base::ChangeCommonSingulars().insert
					(
						std::make_pair(x->Index(),
							std::make_shared
							<Mesh_SingularPatch_Regular
							<
							SurfType,
							typename ModelTraits::sizeFun,
							typename ModelTraits::metricFun>>
							(x, detection)));

					continue;
				}
			}

		}

		if (verbose)
		{
			GET_MESSAGE << " total nb. of surfaces = " << base::Model()->NbSurfaces();
			SEND_INFO;

			GET_MESSAGE << "  - nb. of regular surfaces = " << base::NbRegulars();
			SEND_INFO;

			GET_MESSAGE << "  - nb. of singularities = " << base::NbDeepSingularities();
			SEND_INFO;

			GET_MESSAGE << "  - nb. of common singularities = " << base::NbRegularSingularities();
			SEND_INFO;

			GET_MESSAGE << "  - nb. of defect surfaces = " << base::NbDefects();
			SEND_INFO;
		}

		Change_IsDone() = Standard_True;
	}
}