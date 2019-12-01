#pragma once
#ifndef _CadOpts_PlnIntsct_EdgeEdge_Header
#define _CadOpts_PlnIntsct_EdgeEdge_Header

#include <Global_Done.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CadOpts_PlnIntsct_Edge;
	class CadOpts_PlnIntsct_Info;
	class CadOpts_PlnIntsctEdgeEdge_Data;
	class Pln_Edge;

	class CadOpts_PlnIntsct_EdgeEdge
		: public Global_Done
	{

		typedef CadOpts_PlnIntsct_Info info;

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge0_;
		std::shared_ptr<Pln_Edge> theEdge1_;

		std::shared_ptr<CadOpts_PlnIntsctEdgeEdge_Data> theData_;

		const std::shared_ptr<info>& theInfo_;

	public:

		CadOpts_PlnIntsct_EdgeEdge
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		CadOpts_PlnIntsct_EdgeEdge
		(
			const std::shared_ptr<Pln_Edge>& theEdge0,
			const std::shared_ptr<Pln_Edge>& theEdge1,
			const std::shared_ptr<info>& theInfo
		)
			: theEdge0_(theEdge0)
			, theEdge1_(theEdge1)
			, theInfo_(theInfo)
		{}

		const std::shared_ptr<Pln_Edge>& Edge0() const
		{
			return theEdge0_;
		}

		const std::shared_ptr<Pln_Edge>& Edge1() const
		{
			return theEdge1_;
		}

		const std::shared_ptr<CadOpts_PlnIntsctEdgeEdge_Data>& Data() const
		{
			return theData_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		void LoadEdges
		(
			const std::shared_ptr<Pln_Edge>& theEdge0,
			const std::shared_ptr<Pln_Edge>& theEdge1
		)
		{
			theEdge0_ = theEdge0;
			theEdge1_ = theEdge1;
		}

		void Perform();
	};
}

#endif // !_CadOpts_PlnIntsct_EdgeEdge_Header
