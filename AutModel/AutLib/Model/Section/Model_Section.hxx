#pragma once
#ifndef _Model_Section_Header
#define _Model_Section_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

namespace AutLib
{

	class Model_Section
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

	protected:


		Model_Section()
		{}


		Model_Section
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

		Model_Section
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}


	public:

		virtual ~Model_Section()
		{}


		//- virtual functions and operators

		virtual Standard_Boolean IsHalf() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsFull() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Model_Section_Header
