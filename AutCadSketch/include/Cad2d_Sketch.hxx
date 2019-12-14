#pragma once
#ifndef _Cad2d_Sketch_Header
#define _Cad2d_Sketch_Header

#include <Cad_Sketch.hxx>
#include <Cad2d_Sketch_Engine.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;
	class Pln_Wire;
	class Cad2d_Plane;

	class Geo2d_Circle;
	class Geo2d_LineSegment;
	class Geo2d_Ellipse;


	class Cad2d_Sketch
		: public Cad_Sketch
		, public Cad2d_Sketch_Engine
	{

		/*Private Data*/

	protected:

		Cad2d_Sketch()
		{}

	public:

		void CreateSegment(const std::shared_ptr<Geo2d_LineSegment>& theSegment);

		void CreateCircle(const std::shared_ptr<Geo2d_Circle>& theCircle);

		void CreateEllipse(const std::shared_ptr<Geo2d_Ellipse>& theEllipse);
	};
}

#endif // !_Cad2d_Sketch_Header
