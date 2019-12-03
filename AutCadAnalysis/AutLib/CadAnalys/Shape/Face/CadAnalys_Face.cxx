#include <CadAnalys_Face.hxx>

#include <BRep_Tool.hxx>
#include <ShapeAnalysis.hxx>

void AutLib::CadAnalys_Face::Perform()
{
	theTolerance_ = BRep_Tool::Tolerance(Face());
	
	Standard_Real umin, umax, vmin, vmax;
	ShapeAnalysis::GetFaceUVBounds(Face(), umin, umax, vmin, vmax);

	theOuter_ = ShapeAnalysis::OuterWire(Face());

	theParaBoundingBox_ = Entity2d_Box(Pnt2d(umin, umax), Pnt2d(umax, vmax));

	Change_IsDone() = Standard_True;
}

Standard_Real AutLib::CadAnalys_Face::ContourArea(const TopoDS_Wire& theWire)
{
	return ShapeAnalysis::ContourArea(theWire);
}