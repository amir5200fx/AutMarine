#pragma once
#ifndef _Model_UnSymSection_Header
#define _Model_UnSymSection_Header

#include <Model_Section.hxx>

namespace AutLib
{

	class Model_UnSymSection
		: public Model_Section
	{

		/*Private Data*/

	protected:

		Model_UnSymSection()
		{}

		Model_UnSymSection
		(
			const Standard_Integer theIndex
		)
			: Model_Section(theIndex)
		{}

		Model_UnSymSection
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Model_Section(theIndex, theName)
		{}

	public:


	};
}

#endif // !_Model_UnSymSection_Header
