#pragma once
#ifndef _CadModel_Solid_Header
#define _CadModel_Solid_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <TopoDS_Shape.hxx>

namespace AutLib
{

	class CadModel_Solid
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		TopoDS_Shape theShape_;
		TopoDS_Shape thePreview_;

	protected:

		CadModel_Solid()
		{}

		CadModel_Solid
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~CadModel_Solid()
		{}

		const TopoDS_Shape& Shape() const
		{
			return theShape_;
		}

		const TopoDS_Shape& Preview() const
		{
			return thePreview_;
		}
	};
}

#endif // !_CadModel_Solid_Header
