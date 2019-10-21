#include <Pln_Edge.hxx>

#include <Geo2d_ApprxCurve.hxx>
#include <Cad_CurveInfo.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Vertex.hxx>

void AutLib::Pln_Edge::Discretize() const
{
	Debug_Null_Pointer(theCurve_);
	thePoly_ = Pln_Curve::Discretize(*theCurve_, theCurve_->Info()->NbDivisions());
}

void AutLib::Pln_Edge::Reverse
(
	const Standard_Boolean ApplyToMesh
)
{
	std::swap(theVtx0_, theVtx1_);
	if (ApplyToMesh)
	{
		thePoly_->Reverse();
	}

	Sense_ = NOT Sense_;
}

void AutLib::Pln_Edge::Approx(const info & theInfo) const
{
	Debug_Null_Pointer(theCurve_);
	Geo2d_ApprxCurve approx(theCurve_->Curve(), theCurve_->FirstParam(), theCurve_->LastParam());
	approx.Perform(theInfo);

	auto chain = approx.Chain();

	thePoly_ = std::make_shared<Entity2d_Polygon>();
	Debug_Null_Pointer(thePoly_);

	auto& pts = thePoly_->Points();
	pts = chain->Points();
}

void AutLib::Pln_Edge::Discretize(const Pln_Edge & theEdge)
{
	theEdge.Discretize();
}