#pragma once
#ifndef _CadOpetr_PlnCutter_Header
#define _CadOpetr_PlnCutter_Header

#include <CadOpetr_Cutter.hxx>
#include <Global_AccessMethod.hxx>

#include <gp_Pln.hxx>

#include <memory>

namespace AutLib
{

	class CadOpetr_PlnCutter
		: public CadOpetr_Cutter
	{

		/*Private Data*/

		gp_Pln theCutter_;

	public:

		CadOpetr_PlnCutter
		(
			const gp_Pln& theCutter,
			const TopoDS_Shape& theTarget
		)
			: CadOpetr_Cutter(theTarget)
			, theCutter_(theCutter)
		{}

		CadOpetr_PlnCutter
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const gp_Pln& theCutter,
			const TopoDS_Shape& theTarget
		)
			: CadOpetr_Cutter(theIndex, theName, theTarget)
			, theCutter_(theCutter)
		{}

		void Perform() override;

		//- Macros
		GLOBAL_ACCESS_SINGLE(gp_Pln, Cutter)
	};
}

#endif // !_CadOpetr_PlnCutter_Header
