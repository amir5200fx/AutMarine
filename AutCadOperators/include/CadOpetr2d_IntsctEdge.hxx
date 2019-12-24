#pragma once
#ifndef _CadOpetr2d_IntsctEdge_Header
#define _CadOpetr2d_IntsctEdge_Header

#include <Pln_Edge.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;

	class CadOpetr2d_IntsctEdge
		: public Pln_Edge
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theEdges_;

	protected:

		

	public:

		
	};
}

#endif // !_CadOpetr2d_IntsctEdge_Header
