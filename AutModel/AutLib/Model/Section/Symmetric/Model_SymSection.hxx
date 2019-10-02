#pragma once
#ifndef _Model_SymSection_Header
#define _Model_SymSection_Header

#include <Model_Section.hxx>

namespace AutLib
{

	class Model_SymSection
		: public Model_Section
	{

		/*Private Data*/


	protected:

		Model_SymSection()
		{}

		Model_SymSection(const Standard_Integer theIndex)
			: Model_Section(theIndex)
		{}

		Model_SymSection
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Model_Section(theIndex, theName)
		{}

	public:


	};
}

#endif // !_Model_SymSection_Header
