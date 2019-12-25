#pragma once
#ifndef _CadOpert2d_Split_Header
#define _CadOpert2d_Split_Header

#include <Global_Done.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;
	class Cad2d_Plane;

	class CadOpert2d_Split
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge_;
		std::shared_ptr<Cad2d_Plane> theShape_;

	public:

		CadOpert2d_Split()
		{}

		const std::shared_ptr<Pln_Edge>& Edge() const
		{
			return theEdge_;
		}

		const std::shared_ptr<Cad2d_Plane>& Shape() const
		{
			return theShape_;
		}

		void Perform();
	};
}

#endif // !_CadOpert2d_Split_Header
