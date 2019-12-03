#pragma once
#include <CadAnalys_BadARPatch.hxx>
#include <CadAnalys_DefectPatch_OpenWire.hxx>
#include <CadAnalys_DefectPatch_OrderWire.hxx>

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

			if (CadAnalys_BadARPatch<surfType>::CalcMaxAR(*x))
			{
				base::ChangeDefects().insert
				(
					std::make_pair
					(
						x->Index(),
						std::make_shared
						<
						CadAnalys_BadARPatch<surfType>>(*x)));

				continue;
			}


		}

	}
}