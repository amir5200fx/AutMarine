#pragma once
#ifndef _CrvMaker_Frame_Header
#define _CrvMaker_Frame_Header

#include <Standard_TypeDef.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <OFstream.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CrvMaker_Pole;

	class CrvMaker_Frame
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

	protected:

		CrvMaker_Frame()
		{}

		CrvMaker_Frame(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		CrvMaker_Frame
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual Standard_Boolean IsClosed() const = 0;

		virtual Standard_Integer NbPoles() const = 0;

		virtual const std::shared_ptr<CrvMaker_Pole>& Pole(const Standard_Integer theIndex) const = 0;


		//- Io functions and operatos

		//void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_CrvMaker_Frame_Header
