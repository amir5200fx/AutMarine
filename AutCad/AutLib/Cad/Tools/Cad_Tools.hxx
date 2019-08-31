#pragma once
#ifndef _Cad_Tools_Header
#define _Cad_Tools_Header

#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

class Bnd_Box2d;
class Bnd_Box;

namespace AutLib
{

	class Cad_Tools
	{

	public:

		static Entity2d_Box BoundingBox(const Bnd_Box2d& theBox);

		static Entity3d_Box BoundingBox(const Bnd_Box& theBox);
	};
}

#endif // !_Cad_Tools_Header
