#pragma once
#ifndef _CadOpetr_IntsctEdge_Header
#define _CadOpetr_IntsctEdge_Header

#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;

	class CadOpetr_IntsctEdge
		: public Global_Indexed
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theEdges_;

	protected:

		CadOpetr_IntsctEdge()
		{}

		CadOpetr_IntsctEdge(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

	public:

		const std::vector<std::shared_ptr<Pln_Edge>>& Edges() const
		{
			return theEdges_;
		}

		std::vector<std::shared_ptr<Pln_Edge>>& Edges()
		{
			return theEdges_;
		}

		virtual Standard_Boolean IsCutter() const
		{
			return Standard_False;
		}

	};
}

#endif // !_CadOpetr_IntsctEdge_Header
