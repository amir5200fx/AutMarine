#pragma once
#ifndef _CadOpert2d_IntsctVertx_Header
#define _CadOpetr2d_IntsctVertx_Header


namespace AutLib
{

	// Forward Declarations
	class CadOpert2d_IntsctEdge;

	class CadOpert2d_IntsctVertx
	{

		/*Private Data*/

		std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpert2d_IntsctEdge>
			>
			theIntsctEdges_;

	public:

		

		std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpert2d_IntsctEdge>
			>& IntsctEdges()
		{
			return theIntsctEdges_;
		}

		void InsertToIntsctEdges
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<CadOpert2d_IntsctEdge>& theEdge
		)
		{
			theIntsctEdges_.insert(std::make_pair(theIndex, theEdge));
		}
	};
}

#endif // !_CadOpert2d_IntsctVertx_Header
