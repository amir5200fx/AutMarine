#pragma once
#ifndef _Model_HalfSection_Header
#define _Model_HalfSection_Header

#include <Model_Section.hxx>

namespace AutLib
{

	class Model_HalfSection
		: public Model_Section
	{

		/*private Data*/

	protected:

		Model_HalfSection()
		{}

		Model_HalfSection
		(
			const Standard_Integer theIndex
		)
			: Model_Section(theIndex)
		{}

		Model_HalfSection
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Model_Section(theIndex, theName)
		{}

	public:

		//- override functions and operators

		Standard_Boolean IsHalf() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_Model_HalfSection_Header
