#pragma once
#ifndef _Geo_SizeFunction_Header
#define _Geo_SizeFunction_Header

#include <Standard_TypeDef.hxx>
#include <Global_Done.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>

namespace AutLib
{

	template<class Point>
	class Geo_SizeFunction
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		/*Private Data*/

	protected:

		Geo_SizeFunction()
		{}

		Geo_SizeFunction
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		typedef Point PtType;
		
		//- virtual functions and operators

		virtual Standard_Real Value(const Point& theCoord) const = 0;

		virtual void Perform()
		{
			Change_IsDone() = Standard_True;
		}
	};
}

#endif // !_Geo_SizeFunction_Header
