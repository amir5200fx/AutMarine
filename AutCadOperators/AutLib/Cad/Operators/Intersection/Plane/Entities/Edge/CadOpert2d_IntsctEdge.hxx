#pragma once
#ifndef _CadOpert2d_IntsctEdge_Header
#define _CadOpert2d_IntsctEdge_Header

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;

	class CadOpert2d_IntsctEdge
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theEdges_;

	protected:

		

	public:

		
	};
}

#endif // !_CadOpert2d_IntsctEdge_Header
