#include <Aft2d_CorrOptNode_Iterative.hxx>

#include <Global_Message.hxx>
#include <Aft_CorrOptNode_Iterative_Tools.hxx>
#include <Aft2d_Edge.hxx>

namespace AutLib
{

	template<>
	void Aft2d_CorrOptNode_Iterative::Perform(const Aft_SizeCorr_Iterative_Info& theInfo)
	{
		auto P = P0();
		auto cond = 
			Aft_CorrOptNode_Iterative_Tools::template 
			Correct<Aft2d_Edge, Geo2d_SizeFunction, void, Aft_SizeCorr_Iterative_Info>
			(
				MetricMap(),
				P,
				Front(), theInfo);

		if (cond AND NOT theInfo.IgnoreNonConvergency())
		{
			FatalErrorIn("void Perform()")
				<< "failed to calculate optimized node" << endl
				<< abort(FatalError);
		}

		if (theInfo.Verbose() AND cond)
		{
			GET_MESSAGE << " failed to calculate optimized node" << endl;
			SEND_WARNING;
		}

		ChangeCoord() = std::move(P);
		Change_IsDone() = Standard_True;
	}
}