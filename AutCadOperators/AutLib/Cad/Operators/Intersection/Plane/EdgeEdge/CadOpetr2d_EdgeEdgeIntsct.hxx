#pragma once
#ifndef _CadOpetr2d_EdgeEdgeIntsct_Header
#define _CadOpetr2d_EdgeEdgeIntsct_Header

#include <Global_Done.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CadOpetr2d_IntsctPair;
	class CadOpetr2d_EdgeEdgeIntsct_Info;
	class Pln_Edge;

	class CadOpetr2d_EdgeEdgeIntsct
		: public Global_Done
	{

		typedef CadOpetr2d_EdgeEdgeIntsct_Info info;

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge0_;
		std::shared_ptr<Pln_Edge> theEdge1_;

		std::shared_ptr<info> theInfo_;


		std::vector<std::shared_ptr<CadOpetr2d_IntsctPair>> theEntities_;


		std::vector<std::shared_ptr<CadOpetr2d_IntsctPair>>& ChangeEntities()
		{
			return theEntities_;
		}

	public:

		CadOpetr2d_EdgeEdgeIntsct()
		{}

		CadOpetr2d_EdgeEdgeIntsct
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

		Standard_Integer NbEntities() const
		{
			return (Standard_Integer)theEntities_.size();
		}

		Standard_Boolean HasIntersection() const
		{
			return (Standard_Boolean)theEntities_.size();
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const std::vector<std::shared_ptr<CadOpetr2d_IntsctPair>>& Entities() const
		{
			return theEntities_;
		}

		const std::shared_ptr<CadOpetr2d_IntsctPair>& 
			Entity
			(
				const Standard_Integer theIndex
			) const;

		void LoadEdges
		(
			const std::shared_ptr<Pln_Edge>& theEdge0,
			const std::shared_ptr<Pln_Edge>& theEdge1,
			const std::shared_ptr<info>& theInfo
		)
		{
			theEdge0_ = theEdge0;
			theEdge1_ = theEdge1;

			theInfo_ = theInfo;
		}

		void Perform();

	};
}

#endif // !_CadOpetr2d_EdgeEdgeIntsct_Header
