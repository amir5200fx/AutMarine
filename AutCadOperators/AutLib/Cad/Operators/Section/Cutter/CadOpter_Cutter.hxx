#pragma once
#ifndef _CadOpter_Cutter_Header
#define _CadOpter_Cutter_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <TopoDS_Shape.hxx>

namespace AutLib
{

	class CadOpter_Cutter
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		TopoDS_Shape theTarget_;

		Standard_Boolean RunInParallel_;

		Standard_Boolean ComputePCurveCutter_;
		Standard_Boolean ComputePCurveTarget_;

		TopoDS_Shape theShape_;

	protected:

		CadOpter_Cutter()
			: RunInParallel_(Standard_True)
			, ComputePCurveCutter_(Standard_False)
			, ComputePCurveTarget_(Standard_False)
		{}

		CadOpter_Cutter(const TopoDS_Shape& theTarget)
			: theTarget_(theTarget)
			, RunInParallel_(Standard_True)
			, ComputePCurveCutter_(Standard_False)
			, ComputePCurveTarget_(Standard_False)
		{}

		CadOpter_Cutter
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const TopoDS_Shape& theTarget
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theTarget_(theTarget)
			, RunInParallel_(Standard_True)
			, ComputePCurveCutter_(Standard_False)
			, ComputePCurveTarget_(Standard_False)
		{}


		TopoDS_Shape& ChangeShape()
		{
			return theShape_;
		}

		void SetTarget(const TopoDS_Shape& theTarget)
		{
			theTarget_ = theTarget;
		}

	public:

		virtual ~CadOpter_Cutter()
		{}

		const TopoDS_Shape& Target() const
		{
			return theTarget_;
		}

		const TopoDS_Shape& Shape() const
		{
			return theShape_;
		}

		Standard_Boolean RunInParallel() const
		{
			return RunInParallel_;
		}

		virtual void Perform() = 0;

		void SetRunInParallel(const Standard_Boolean set)
		{
			RunInParallel_ = set;
		}

		void SetComputePCurveCutter(const Standard_Boolean set)
		{
			ComputePCurveCutter_ = set;
		}

		void SetComputePCurveTarget(const Standard_Boolean set)
		{
			ComputePCurveTarget_ = set;
		}
	};
}

#endif // !_CadOpter_Cutter_Header
