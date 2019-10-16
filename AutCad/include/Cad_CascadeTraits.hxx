#pragma once
#ifndef _Cad_CascadeTraits_Header
#define _Cad_CascadeTraits_Header

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>

class Geom2d_Curve;
class Geom_Curve;

namespace AutLib
{

	namespace cascadeLib
	{

		template<class T> struct pt_type_from_curve {};

		template<> struct pt_type_from_curve<Geom2d_Curve> { typedef Pnt2d ptType; };
		template<> struct pt_type_from_curve<Geom_Curve> { typedef Pnt3d ptType; };
	}
}

#endif // !_Cad_CascadeTraits_Header
