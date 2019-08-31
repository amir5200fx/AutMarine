#include <IO_IGES.hxx>

#include <Global_Timer.hxx>
#include <Global_Message.hxx>
#include <Pnt3d.hxx>
#include <Cad_Tools.hxx>
#include <FastDiscrete.hxx>
#include <OStringStream.hxx>

#include <BRepBndLib.hxx>
#include <ShapeFix_Shape.hxx>
#include <IGESControl_Reader.hxx>
#include <BRepMesh_FastDiscret.hxx>

void AutLib::IO_IGES::doFixShape()
{
	if (Verbose())
	{
		GET_MESSAGE << "fixing the shape...";
		SEND_INFO;
	}

	Handle(ShapeFix_Shape) fixShape = new ShapeFix_Shape;

	fixShape->Init(Shape());

	Standard_Real dia = Distance(BoundingBox().P0(), BoundingBox().P1());

	if (Verbose())
	{
		GET_MESSAGE << "min corner= [" << BoundingBox().P0() 
			<< "], max corner= [" << BoundingBox().P1() << "]";
		SEND_INFO;
	}

	fixShape->SetPrecision(dia*Precision());
	fixShape->SetMaxTolerance(dia*MaxTol());
	fixShape->SetMinTolerance(dia*MinTol());
	fixShape->Perform();

	if (Verbose())
	{
		GET_MESSAGE << "precision: " << Precision();
		SEND_INFO;

		GET_MESSAGE << "max tolerance: " << MaxTol();
		SEND_INFO;

		GET_MESSAGE << "min tolerance: " << MinTol();
		SEND_INFO;
	}

	if (Verbose())
	{

		GET_MESSAGE << " ShapeExtendOK = " 
			<< fixShape->Status(ShapeExtend_OK);
		SEND_INFO;
		
		GET_MESSAGE << " ShapeExtend_DONE1 = " 
			<< fixShape->Status(ShapeExtend_DONE1);
		SEND_INFO;

		GET_MESSAGE << " ShapeExtend_DONE2 = " 
			<< fixShape->Status(ShapeExtend_DONE2);
		SEND_INFO;

		GET_MESSAGE << " ShapeExtend_DONE3 = " 
			<< fixShape->Status(ShapeExtend_DONE3);
		SEND_INFO;

		GET_MESSAGE << " ShapeExtend_DONE4 = " 
			<< fixShape->Status(ShapeExtend_DONE4);
		SEND_INFO;

		GET_MESSAGE << " ShapeExtend_DONE5 = " 
			<< fixShape->Status(ShapeExtend_DONE5);
		SEND_INFO;

		GET_MESSAGE << " ShapeExtend_DONE6 = " 
			<< fixShape->Status(ShapeExtend_DONE6);
		SEND_INFO;

		GET_MESSAGE << " ShapeExtend_DONE7 = " 
			<< fixShape->Status(ShapeExtend_DONE7);
		SEND_INFO;

		GET_MESSAGE << " ShapeExtend_DONE8 = " 
			<< fixShape->Status(ShapeExtend_DONE8);
		SEND_INFO;
	}

	SetShape(fixShape->Shape());
}

void AutLib::IO_IGES::ReadFile
(
	const word & theFileName
)
{
	{ // timer scope
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_s);

		IGESControl_Reader Reader;

		Reader.ReadFile(theFileName.c_str());

		Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("iges-faces");
		SetNbIgesFaces(myList->Length());
		SetNbTransFaces(Reader.TransferList(myList));

		SetShape(Reader.OneShape());
		SetFileName(theFileName);
		SetName(theFileName);

		Bnd_Box box;

		if (FixShape())
		{
			BRepBndLib::Add(Shape(), box);

			SetBoundingBox(Cad_Tools::BoundingBox(box));

			doFixShape();
		}

		BRepBndLib::Add(Shape(), box);

		SetBoundingBox(Cad_Tools::BoundingBox(box));

		if (Discrete())
		{
			if (Verbose())
			{
				GET_MESSAGE << "Discretization of the shape...";
				SEND_INFO;
			}

			Debug_Null_Pointer(FastDiscreteParams());
			FastDiscrete::Triangulation(Shape(), box, *FastDiscreteParams());
		}
	}

	if (Verbose())
	{
		GET_MESSAGE << "IGES File Imported Successfully in "
			<< global_time_duration << " seconds.";
		SEND_INFO;

		GET_MESSAGE << "File Name: " << FileName();
		SEND_INFO;

		GET_MESSAGE << "Model Name: " << Name();
		SEND_INFO;
	}
}