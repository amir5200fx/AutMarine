#pragma once
#ifndef _CadOpert2d_IntsctSubEdge_Tang_Header
#define _CadOpert2d_IntsctSubEdge_Tang_Header

#include <CadOpert2d_IntsctSubEdge.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpert2d_IntsctSegment;

	class CadOpert2d_IntsctSubEdge_Tang
		: public CadOpert2d_IntsctSubEdge
	{

		/*Private Data*/

		std::shared_ptr<CadOpert2d_IntsctSegment> theEntity_;

		std::weak_ptr<CadOpert2d_IntsctSubEdge_Tang> thePair_;

	public:

		CadOpert2d_IntsctSubEdge_Tang
		(
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True,
			const Standard_Boolean Discrete = Standard_False
		)
			: CadOpert2d_IntsctSubEdge(theV0, theV1, theCurve, Sense, Discrete)
		{}

		CadOpert2d_IntsctSubEdge_Tang
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True,
			const Standard_Boolean Discrete = Standard_False
		)
			: CadOpert2d_IntsctSubEdge(theIndex, theV0, theV1, theCurve, Sense, Discrete)
		{}

		CadOpert2d_IntsctSubEdge_Tang
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True,
			const Standard_Boolean Discrete = Standard_False
		)
			: CadOpert2d_IntsctSubEdge(theIndex, theName, theV0, theV1, theCurve, Sense, Discrete)
		{}


		Standard_Boolean IsTangential() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpert2d_IntsctSegment>, Entity)
			GLOBAL_ACCESS_SINGLE(std::weak_ptr<CadOpert2d_IntsctSubEdge_Tang>, Pair)
	};
}

#endif // !_CadOpert2d_IntsctSubEdge_Tang_Header
