#include <Aft2d_CorrOptNode_Fraction.hxx>

#include <Aft2d_OptNode_Analytical.hxx>

namespace AutLib
{

	template<>
	void Aft2d_CorrOptNode_Fraction::Perform
	(
		const Aft_SizeCorr_Fraction_Info& theInfo
	)
	{

		const auto h1 = Size();
		const auto h2 = MetricMap().CalcElementSize(P0());

		if (h2 >= h1)
		{
			ChangeCoord() = P0();
		}
		else
		{
			auto h = h1;

			const auto delta = theInfo.Delta();	
			const auto frac = (h1 - h2) / h1;

			if (frac <= delta)
			{
				/*continue*/
			}
			else
			{
				const auto w = theInfo.Coeff();
				h = w * h1 + ((Standard_Real)1.0 - w)*h2;
			}

			Aft2d_OptNode_Analytical optNode(h, Front());
			optNode.Perform();

			ChangeCoord() = optNode.Coord();
		}
		
		Change_IsDone() = Standard_True;
		Change_IsConverged() = Standard_True;		
	}
}