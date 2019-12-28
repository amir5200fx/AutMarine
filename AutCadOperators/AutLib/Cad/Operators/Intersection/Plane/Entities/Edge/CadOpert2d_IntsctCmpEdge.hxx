#pragma once
#ifndef _CadOpert2d_IntsctCmpEdge_Header
#define _CadOpert2d_IntsctCmpEdge_Header

#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;

	class CadOpert2d_IntsctCmpEdge
		: public Global_Indexed
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theEdges_;

	protected:

		CadOpert2d_IntsctCmpEdge()
		{}

		CadOpert2d_IntsctCmpEdge
		(
			const Standard_Integer theIndex
		)
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

		virtual Standard_Boolean IsSubEdge() const
		{
			return Standard_False;
		}
	};
}

#endif // !_CadOpert2d_IntsctCmpEdge_Header
