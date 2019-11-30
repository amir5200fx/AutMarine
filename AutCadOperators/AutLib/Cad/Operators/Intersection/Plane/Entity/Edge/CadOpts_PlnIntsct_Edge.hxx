#pragma once
#ifndef _CadOpts_PlnIntsct_Edge_Header
#define _CadOpts_PlnIntsct_Edge_Header

#include <Pln_CmpEdge.hxx>

namespace AutLib
{

	// Forward Declarations
	class CadOpts_PlnIntsct_Vertex;

	class CadOpts_PlnIntsct_Edge
		: public Pln_CmpEdge
	{

		/*Private Data*/

		std::shared_ptr<CadOpts_PlnIntsct_Vertex> theVtx0_;
		std::shared_ptr<CadOpts_PlnIntsct_Vertex> theVtx1_;

	protected:

		CadOpts_PlnIntsct_Edge()
		{}

		CadOpts_PlnIntsct_Edge
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Pln_CmpEdge(theIndex, theName)
		{}

	public:

		const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& Vtx0() const
		{
			return theVtx0_;
		}

		const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& Vtx1() const
		{
			return theVtx1_;
		}

		virtual Standard_Boolean IsSegment1() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSegment2() const
		{
			return Standard_False;
		}

		void Insert(const std::shared_ptr<Pln_Edge>& theEdge) override;

		void SetVtx0(const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& theVtx)
		{
			theVtx0_ = theVtx;
		}

		void SetVtx1(const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& theVtx)
		{
			theVtx1_ = theVtx;
		}

		Standard_Boolean IsForward(const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& theVertex);

		Standard_Boolean IsBackward(const std::shared_ptr<CadOpts_PlnIntsct_Vertex>& theVertex);

		//- Static functions

		
	};

}

#endif // !_CadOpts_PlnIntsct_Edge_Header
