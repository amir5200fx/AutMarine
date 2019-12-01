#pragma once
#ifndef _CadOpts_PlnSubdivide_Edge_Header
#define _CadOpts_PlnSubdivide_Edge_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;
	class CadOpts_PlnSubdivide_Data;

	class CadOpts_PlnSubdivide_Edge
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge1_;
		std::shared_ptr<Pln_Edge> theEdge2_;

		std::shared_ptr<CadOpts_PlnSubdivide_Data> theData1_;
		std::shared_ptr<CadOpts_PlnSubdivide_Data> theData2_;

		std::vector<std::shared_ptr<Pln_Edge>> theEdges1_;
		std::vector<std::shared_ptr<Pln_Edge>> theEdges2_;

	public:

		CadOpts_PlnSubdivide_Edge()
		{}

		CadOpts_PlnSubdivide_Edge
		(
			const std::shared_ptr<Pln_Edge>& theEdge1,
			const std::shared_ptr<CadOpts_PlnSubdivide_Data>& theData1, 
			const std::shared_ptr<Pln_Edge>& theEdge2,
			const std::shared_ptr<CadOpts_PlnSubdivide_Data>& theData2
		)
			: theEdge1_(theEdge1)
			, theEdge2_(theEdge2)
			, theData1_(theData1)
			, theData2_(theData2)
		{}

		const std::vector<std::shared_ptr<Pln_Edge>>& Edges1() const
		{
			return theEdges1_;
		}

		const std::vector<std::shared_ptr<Pln_Edge>>& Edges2() const
		{
			return theEdges2_;
		}

		void Perform();

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Pln_Edge>, Edge1)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Pln_Edge>, Edge2)

			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpts_PlnSubdivide_Data>, Data1)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpts_PlnSubdivide_Data>, Data2)
	};


	
}

#endif // !_CadOpts_PlnSubdivide_Edge_Header
