#include <Numeric_NewtonSolver.hxx>

namespace AutLib
{
	const Standard_Integer Numeric_NewtonSolverInfo::MAX_NB_ITERATIONS(500);

	const Standard_Real Numeric_NewtonSolverInfo::DEFAULT_UNDER_RELAXATION(0.9);
	const Standard_Real Numeric_NewtonSolverInfo::DEFAULT_TOLERANCE(1.0E-8);
	const Standard_Real Numeric_NewtonSolverInfo::DEFAULT_ZERO((Standard_Real)VSMALL);
	const Standard_Real Numeric_NewtonSolverInfo::DEFAULT_SMALL((Standard_Real)1.0E-6);
}