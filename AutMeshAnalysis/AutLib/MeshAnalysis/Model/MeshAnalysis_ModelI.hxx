#pragma once
#include <Global_Message.hxx>
#include <CadRepair_ParaPlaneAR.hxx>
#include <CadRepair_NormalizeMetric.hxx>
#include <CadRepair_ParaPlaneAR_Info.hxx>
#include <CadRepair_NormalizeMetric_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class SizeFun, class CurveType, class SurfType>
	void MeshAnalysis_Model<SizeFun, CurveType, SurfType>::Perform()
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

			if (base::Info()->EqualizerMetricInfo()->ToApply())
			{

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
				planeEqual->Perform();

				Debug_If_Condition_Message(NOT planeEqual->IsDone(), " the metric equalizer has not been performed!");

				if (planeEqual->Applied())
				{
					x = planeEqual->Modified();
				}
			}


		}
	}
}