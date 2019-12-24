#pragma once
#ifndef _CadOpter_PlnCutter_Header
#define _CadOpter_PlnCutter_Header

#include <CadOpter_Cutter.hxx>
#include <Global_AccessMethod.hxx>

#include <gp_Pln.hxx>

#include <memory>

namespace AutLib
{

	class CadOpter_PlnCutter
		: public CadOpter_Cutter
	{

		/*Private Data*/

		gp_Pln theCutter_;

	public:

		CadOpter_PlnCutter
		(
			const gp_Pln& theCutter,
			const TopoDS_Shape& theTarget
		)
			: CadOpter_Cutter(theTarget)
			, theCutter_(theCutter)
		{}

		CadOpter_PlnCutter
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const gp_Pln& theCutter,
			const TopoDS_Shape& theTarget
		)
			: CadOpter_Cutter(theIndex, theName, theTarget)
			, theCutter_(theCutter)
		{}

		void Perform() override;

		//- Macros
		GLOBAL_ACCESS_SINGLE(gp_Pln, Cutter)
	};
}

#endif // !_CadOpter_PlnCutter_Header
