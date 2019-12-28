#pragma once
#ifndef _CadOpert2d_IntsctSubEdge_Header
#define _CadOpert2d_IntsctSubEdge_Header

#include <Pln_Edge.hxx>

namespace AutLib
{

	

	class CadOpert2d_IntsctSubEdge
		: public Pln_Edge
	{

		/*Private Data*/

		

	public:

		CadOpert2d_IntsctSubEdge
		(
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True,
			const Standard_Boolean Discrete = Standard_False
		)
			: Pln_Edge(theV0, theV1, theCurve, Sense, Discrete)
		{}

		CadOpert2d_IntsctSubEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True,
			const Standard_Boolean Discrete = Standard_False
		)
			: Pln_Edge(theIndex, theV0, theV1, theCurve, Sense, Discrete)
		{}

		CadOpert2d_IntsctSubEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True,
			const Standard_Boolean Discrete = Standard_False
		)
			: Pln_Edge(theIndex, theName, theV0, theV1, theCurve, Sense, Discrete)
		{}

		Standard_Boolean IsIntersection() const override
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}

		
	};
}

#endif // !_CadOpert2d_IntsctSubEdge_Header
