#pragma once
#ifndef _CadOpert2d_Split_Header
#define _CadOpert2d_Split_Header

#include <Global_Done.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_CmpEdge;
	class Cad2d_Plane;
	class CadOpert2d_EdgeEdgeIntsct_Info;

	class CadOpert2d_Split
		: public Global_Done
	{

		typedef CadOpert2d_EdgeEdgeIntsct_Info info;

		/*Private Data*/

		std::shared_ptr<Pln_CmpEdge> theEdge_;
		std::shared_ptr<Cad2d_Plane> theShape_;

		std::shared_ptr<info> theInfo_;

	public:

		CadOpert2d_Split()
		{}

		const std::shared_ptr<Pln_CmpEdge>& Edge() const
		{
			return theEdge_;
		}

		const std::shared_ptr<Cad2d_Plane>& Shape() const
		{
			return theShape_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		void Perform();
	};
}

#endif // !_CadOpert2d_Split_Header
