#pragma once
#ifndef _CadOpetr2d_IntsctCmpEdge_Header
#define _CadOpetr2d_IntsctCmpEdge_Header

#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class CadOpetr2d_IntsctEdge;

	class CadOpetr2d_IntsctCmpEdge
		: public Global_Indexed
	{

		/*Private Data*/

		std::vector<std::shared_ptr<CadOpetr2d_IntsctEdge>> theEdges_;

	public:

		CadOpetr2d_IntsctCmpEdge()
		{}

		CadOpetr2d_IntsctCmpEdge(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		const std::vector<std::shared_ptr<CadOpetr2d_IntsctEdge>>& Edges() const
		{
			return theEdges_;
		}

		std::vector<std::shared_ptr<CadOpetr2d_IntsctEdge>>& Edges()
		{
			return theEdges_;
		}

		virtual Standard_Boolean IsCutter() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSubdivided() const
		{
			return Standard_False;
		}
	};
}

#endif // !_CadOpetr2d_IntsctCmpEdge_Header
