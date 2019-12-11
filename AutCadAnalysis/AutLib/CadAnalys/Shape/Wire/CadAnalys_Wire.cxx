#include <CadAnalys_Wire.hxx>

#include <Global_Message.hxx>
#include <CadAnalys_Wire_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <ShapeExtend_Status.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeFix_Wire.hxx>

void AutLib::CadAnalys_Wire::Perform()
{
	if (Face().IsNull())
	{
		FatalErrorIn("void Perform()")
			<< " no face has been loaded!" << endl
			<< abort(FatalError);
	}

	if (Wire().IsNull())
	{
		FatalErrorIn("void Perform()")
			<< " no wire has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto prec = Info()->Precision();
	const auto smallPrec = Info()->SmallPrecision();

	Handle(ShapeAnalysis_Wire) analys = new ShapeAnalysis_Wire(Wire(), Face(), prec);
	Debug_Null_Pointer(analys);
	
	if (NOT analys->IsLoaded())
	{
		FatalErrorIn("void Perform()")
			<< "wire is not loaded" << endl
			<< abort(FatalError);
	}

	if (NOT analys->IsReady())
	{
		FatalErrorIn("void Perform()")
			<< "face is not loaded" << endl
			<< abort(FatalError);
	}

	Order2d_ = analys->CheckOrder(Standard_True, Standard_False);
	Order3d_ = analys->CheckOrder();

	if (Order2d_ OR Order3d_)
	{
		ShapeFix_Wire fix(Wire(), Face(), prec);
		fix.FixReorder();

		Order2d_ = analys->CheckOrder(Standard_True, Standard_False);
		Order3d_ = analys->CheckOrder();

		if (Order2d_ OR Order3d_)
		{
			FatalErrorIn("void Perform()")
				<< "unable to fix the order issue of the wire" << endl
				<< abort(FatalError);
		}
	}
		
	Small_ = analys->CheckSmall(smallPrec);
	Connected_ = analys->CheckConnected(prec);
	EdgeCurves_ = analys->CheckEdgeCurves();
	Degenerated_ = analys->CheckDegenerated();
	SelfIntersection_ = analys->CheckSelfIntersection();
	Lacking_ = analys->CheckLacking();
	Closed_ = analys->CheckClosed(prec);

	theMinDist3d_ = analys->MinDistance3d();
	theMaxDist3d_ = analys->MaxDistance3d();
	theMinDist2d_ = analys->MinDistance2d();
	theMaxDist2d_ = analys->MaxDistance2d();

	theNbEdges_ = analys->NbEdges();

	theAnalysis_ = analys;
}