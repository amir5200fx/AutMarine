#pragma once
#ifndef _CadModel_Profile_Header
#define _CadModel_Profile_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <OFstream.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace AutLib
{

	template<class PoleType>
	class CadModel_Profile
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/


	protected:

		CadModel_Profile()
		{}

		CadModel_Profile
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual Standard_Boolean IsPrime() const
		{
			return Standard_False;
		}

		virtual Standard_Integer NbPoles() const = 0;

		const std::shared_ptr<PoleType>& Pole(const Standard_Integer theIndex) const = 0;

		void ExportToPlt(OFstream& theFile) const;
	};
}

#endif // !_CadModel_Profile_Header
