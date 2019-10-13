#pragma once
#ifndef _Numeric_GuassQuadratureNodes_Header
#define _Numeric_GuassQuadratureNodes_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	namespace numLib
	{

		namespace gaussLib
		{

			template<int Node, int NbNodes>
			struct IntgNode {};

			template<> struct IntgNode<0, 2> { static const Standard_Real value; };

			template<> struct IntgNode<0, 4> { static const Standard_Real value; };
			template<> struct IntgNode<1, 4> { static const Standard_Real value; };

			template<> struct IntgNode<0, 6> { static const Standard_Real value; };
			template<> struct IntgNode<1, 6> { static const Standard_Real value; };
			template<> struct IntgNode<2, 6> { static const Standard_Real value; };

			template<> struct IntgNode<0, 8> { static const Standard_Real value; };
			template<> struct IntgNode<1, 8> { static const Standard_Real value; };
			template<> struct IntgNode<2, 8> { static const Standard_Real value; };
			template<> struct IntgNode<3, 8> { static const Standard_Real value; };


			template<> struct IntgNode<0, 10> { static const Standard_Real value; };
			template<> struct IntgNode<1, 10> { static const Standard_Real value; };
			template<> struct IntgNode<2, 10> { static const Standard_Real value; };
			template<> struct IntgNode<3, 10> { static const Standard_Real value; };
			template<> struct IntgNode<4, 10> { static const Standard_Real value; };


			template<> struct IntgNode<0, 12> { static const Standard_Real value; };
			template<> struct IntgNode<1, 12> { static const Standard_Real value; };
			template<> struct IntgNode<2, 12> { static const Standard_Real value; };
			template<> struct IntgNode<3, 12> { static const Standard_Real value; };
			template<> struct IntgNode<4, 12> { static const Standard_Real value; };
			template<> struct IntgNode<5, 12> { static const Standard_Real value; };


			template<> struct IntgNode<0, 14> { static const Standard_Real value; };
			template<> struct IntgNode<1, 14> { static const Standard_Real value; };
			template<> struct IntgNode<2, 14> { static const Standard_Real value; };
			template<> struct IntgNode<3, 14> { static const Standard_Real value; };
			template<> struct IntgNode<4, 14> { static const Standard_Real value; };
			template<> struct IntgNode<5, 14> { static const Standard_Real value; };
			template<> struct IntgNode<6, 14> { static const Standard_Real value; };


			template<> struct IntgNode<0, 16> { static const Standard_Real value; };
			template<> struct IntgNode<1, 16> { static const Standard_Real value; };
			template<> struct IntgNode<2, 16> { static const Standard_Real value; };
			template<> struct IntgNode<3, 16> { static const Standard_Real value; };
			template<> struct IntgNode<4, 16> { static const Standard_Real value; };
			template<> struct IntgNode<5, 16> { static const Standard_Real value; };
			template<> struct IntgNode<6, 16> { static const Standard_Real value; };
			template<> struct IntgNode<7, 16> { static const Standard_Real value; };


			template<> struct IntgNode<0, 18> { static const Standard_Real value; };
			template<> struct IntgNode<1, 18> { static const Standard_Real value; };
			template<> struct IntgNode<2, 18> { static const Standard_Real value; };
			template<> struct IntgNode<3, 18> { static const Standard_Real value; };
			template<> struct IntgNode<4, 18> { static const Standard_Real value; };
			template<> struct IntgNode<5, 18> { static const Standard_Real value; };
			template<> struct IntgNode<6, 18> { static const Standard_Real value; };
			template<> struct IntgNode<7, 18> { static const Standard_Real value; };
			template<> struct IntgNode<8, 18> { static const Standard_Real value; };


			template<> struct IntgNode<0, 20> { static const Standard_Real value; };
			template<> struct IntgNode<1, 20> { static const Standard_Real value; };
			template<> struct IntgNode<2, 20> { static const Standard_Real value; };
			template<> struct IntgNode<3, 20> { static const Standard_Real value; };
			template<> struct IntgNode<4, 20> { static const Standard_Real value; };
			template<> struct IntgNode<5, 20> { static const Standard_Real value; };
			template<> struct IntgNode<6, 20> { static const Standard_Real value; };
			template<> struct IntgNode<7, 20> { static const Standard_Real value; };
			template<> struct IntgNode<8, 20> { static const Standard_Real value; };
			template<> struct IntgNode<9, 20> { static const Standard_Real value; };

		}
	}
}

#endif // !_Numeric_GuassQuadratureNodes_Header
