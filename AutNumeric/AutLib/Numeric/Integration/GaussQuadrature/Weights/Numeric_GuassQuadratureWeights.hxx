#pragma once
#ifndef _Numeric_GuassQuadratureWeights_Header
#define _Numeric_GuassQuadratureWeights_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	namespace numLib
	{

		namespace guassLib
		{

			template<int Node, int NbNodes>
			struct IntgWeight {};

			template<> struct IntgWeight<0, 2> { static const Standard_Real value; };

			template<> struct IntgWeight<0, 4> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 4> { static const Standard_Real value; };

			template<> struct IntgWeight<0, 6> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 6> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 6> { static const Standard_Real value; };

			template<> struct IntgWeight<0, 8> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 8> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 8> { static const Standard_Real value; };
			template<> struct IntgWeight<3, 8> { static const Standard_Real value; };


			template<> struct IntgWeight<0, 10> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 10> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 10> { static const Standard_Real value; };
			template<> struct IntgWeight<3, 10> { static const Standard_Real value; };
			template<> struct IntgWeight<4, 10> { static const Standard_Real value; };


			template<> struct IntgWeight<0, 12> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 12> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 12> { static const Standard_Real value; };
			template<> struct IntgWeight<3, 12> { static const Standard_Real value; };
			template<> struct IntgWeight<4, 12> { static const Standard_Real value; };
			template<> struct IntgWeight<5, 12> { static const Standard_Real value; };


			template<> struct IntgWeight<0, 14> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 14> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 14> { static const Standard_Real value; };
			template<> struct IntgWeight<3, 14> { static const Standard_Real value; };
			template<> struct IntgWeight<4, 14> { static const Standard_Real value; };
			template<> struct IntgWeight<5, 14> { static const Standard_Real value; };
			template<> struct IntgWeight<6, 14> { static const Standard_Real value; };


			template<> struct IntgWeight<0, 16> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 16> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 16> { static const Standard_Real value; };
			template<> struct IntgWeight<3, 16> { static const Standard_Real value; };
			template<> struct IntgWeight<4, 16> { static const Standard_Real value; };
			template<> struct IntgWeight<5, 16> { static const Standard_Real value; };
			template<> struct IntgWeight<6, 16> { static const Standard_Real value; };
			template<> struct IntgWeight<7, 16> { static const Standard_Real value; };


			template<> struct IntgWeight<0, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<3, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<4, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<5, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<6, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<7, 18> { static const Standard_Real value; };
			template<> struct IntgWeight<8, 18> { static const Standard_Real value; };


			template<> struct IntgWeight<0, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<1, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<2, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<3, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<4, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<5, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<6, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<7, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<8, 20> { static const Standard_Real value; };
			template<> struct IntgWeight<9, 20> { static const Standard_Real value; };
		}
	}
}

#endif // !_Numeric_GuassQuadratureWeights_Header
