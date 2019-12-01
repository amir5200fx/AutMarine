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

void AutLib::Pln_Edge::Approx(const std::shared_ptr<info>& theInfo) const
{
	Debug_Null_Pointer(theCurve_);
	Geo2d_ApprxCurve approx(theCurve_->Curve(), theCurve_->FirstParam(), theCurve_->LastParam(), theInfo);
	approx.Perform();

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

void AutLib::Pln_Edge::Split
(
	const Standard_Real x, 
	std::shared_ptr<Pln_Vertex>& theVertex,
	std::shared_ptr<Pln_Edge>& theLeft, 
	std::shared_ptr<Pln_Edge>& theRight
) const
{
	Debug_Null_Pointer(Curve());
	const auto& curve = *Curve();

	if (NOT INSIDE(x, curve.FirstParam(), curve.LastParam()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Data: the parameter is outside the parametric bounds"
			<< " - parameter: " << x << endl
			<< " - first = " << curve.FirstParam() << ", last = " << curve.LastParam() << endl
			<< abort(FatalError);
	}

	Pnt2d pt;
	std::shared_ptr<Pln_Curve> c1, c2;
	curve.Split(x, pt, c1, c2);

	Debug_Null_Pointer(c1);
	Debug_Null_Pointer(c2);

	auto vtx = std::make_shared<Pln_Vertex>(0, pt);

	auto edge1 = std::make_shared<Pln_Edge>(Vtx0(), vtx, c1, Sense());
	auto edge2 = std::make_shared<Pln_Edge>(vtx, Vtx1(), c2, Sense());
}