#pragma once
#ifndef _Mesh_OptNode_IterativeCorrectorInfo_Header
#define _Mesh_OptNode_IterativeCorrectorInfo_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Verbose.hxx>

namespace AutLib
{

	class Mesh_OptNode_IterativeCorrectorInfo
		: public Global_Verbose
	{

		/*Private Data*/

		Standard_Integer theMaxNbIters_;

		Standard_Real theTolerance_;
		Standard_Real theUnderRelaxation_;

		Standard_Boolean IgnoreNonConvergency_;

	public:

		static const Standard_Integer DEFAULT_MAX_NB_ITERATIONS;

		static const Standard_Real DEFAULT_TOLERANCE;
		static const Standard_Real DEFAULT_UNDER_RELAXATION;

		Mesh_OptNode_IterativeCorrectorInfo()
			: theMaxNbIters_(DEFAULT_MAX_NB_ITERATIONS)
			, theTolerance_(DEFAULT_TOLERANCE)
			, theUnderRelaxation_(DEFAULT_UNDER_RELAXATION)
			, IgnoreNonConvergency_(Standard_False)
		{}

		Standard_Boolean IgnoreNonConvergency() const
		{
			return IgnoreNonConvergency_;
		}

		void SetIgnoreNonConvergency(const Standard_Boolean theConv)
		{
			IgnoreNonConvergency_ = theConv;
		}

		//- Macros

		GLOBAL_ACCESS_SINGLE(Standard_Integer, MaxNbIters)
			GLOBAL_ACCESS_SINGLE(Standard_Real, Tolerance)
			GLOBAL_ACCESS_SINGLE(Standard_Real, UnderRelaxation)
	};
}

#endif // !_Mesh_OptNode_IterativeCorrectorInfo_Header
