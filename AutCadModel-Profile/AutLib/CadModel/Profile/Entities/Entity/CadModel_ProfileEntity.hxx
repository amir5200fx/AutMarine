#pragma once
#ifndef _CadModel_ProfileEntity_Header
#define _CadModel_ProfileEntity_Header

#include <Global_Indexed.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace AutLib
{

	class CadModel_ProfileEntity
		: public Global_Indexed
	{

		/*private Data*/

	protected:

		CadModel_ProfileEntity()
		{}

		CadModel_ProfileEntity
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

	public:

		virtual ~CadModel_ProfileEntity()
		{}
	};
}

#endif // !_CadModel_ProfileEntity_Header
