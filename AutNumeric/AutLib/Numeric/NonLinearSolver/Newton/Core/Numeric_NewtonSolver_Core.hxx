#pragma once
#ifndef _Numeric_NewtonSolver_Core_Header
#define _Numeric_NewtonSolver_Core_Header

namespace AutLib
{

	template<class Function, class Derivation>
	class Numeric_NewtonSolver_Core
		: public Function
		, public Derivation
	{

		typedef Function fun;
		typedef Derivation der;

		/*Private Data*/

		virtual Standard_Boolean& Change_IsDone() = 0;

		virtual Standard_Integer& ChangeNbIter() = 0;

		virtual NewtonIterCondition Condition() const = 0;

		virtual NewtonIterCondition& ChangeCondition() = 0;

		virtual Standard_Real& ChangeResidual() = 0;

		virtual Standard_Real& ChangeResult() = 0;

		virtual Standard_Integer MaxNbIterations() const = 0;

		virtual Standard_Real UnderRelaxation() const = 0;

		virtual Standard_Real Tolerance() const = 0;

		virtual Standard_Real Zero() const = 0;

		virtual Standard_Real Small() const = 0;

	protected:

		Numeric_NewtonSolver_Core
		(
			const Function& theFunction,
			const Derivation& theDerivation
		)
			: fun(theFunction)
			, der(theDerivation)
		{}

	public:

		void Perform(const Standard_Real guess)
		{
			Change_IsDone() = Standard_True;

			auto u = guess;

			fun::CheckBound(u);
			auto y0 = fun::Value(u);

			Standard_Real df, dp, p1, y1, rel_err;

			ChangeNbIter() = 0;
			ChangeResidual() = (Standard_Real)0.;
			ChangeResult() = (Standard_Real)0.;
			ChangeCondition() = NewtonIter_LEVEL_EXCEEDED;

			forThose(Iter, 1, MaxNbIterations())
			{
				ChangeNbIter()++;

				der::CheckBound(u);
				df = der::Value(u);

				if (ABS(df) <= Zero())
				{
					dp = (Standard_Real)0.;
					ChangeCondition() = NewtonIter_ZERODIVIDE;
				}
				else
					dp = y0 / df;

				p1 = u - UnderRelaxation()*dp;

				fun::CheckBound(p1);
				y1 = fun::Value(p1);

				rel_err = (Standard_Real)2.0 * ABS(dp) / (ABS(p1) + Small());

				if (rel_err < Tolerance() OR ABS(y1) < Zero())
					if (Condition() NOT_EQUAL NewtonIter_ZERODIVIDE)
						ChangeCondition() = NewtonIter_CONVERGED;

				u = p1;
				y0 = y1;

				if (Condition())
					break;
			}

			ChangeResult() = u;
			ChangeResidual() = rel_err;
		}
	};
}

#endif // !_Numeric_NewtonSolver_Core_Header
