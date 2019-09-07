#include <Pln_Curve.hxx>

#include <GeoProcessor.hxx>

#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>

Standard_Real AutLib::Pln_Curve::CalcCurvature
(
	const Standard_Real theParameter
) const
{
	if (NOT INSIDE(theParameter, FirstParam(), LastParam()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Parameter" << endl
			<< " - first= " << FirstParam() << endl
			<< " - last= " << LastParam() << endl
			<< "- parameter= " << theParameter << endl
			<< abort(FatalError);
	}

	gp_Pnt2d Point;
	gp_Vec2d Vector1;
	gp_Vec2d Vector2;

	Debug_Null_Pointer(Curve());

	Curve()->D2(theParameter, Point, Vector1, Vector2);
	return ABS(Vector1.Crossed(Vector2)) / (pow(Vector1.Magnitude(), 3));
}

AutLib::Pnt2d
AutLib::Pln_Curve::Value
(
	const Standard_Real theParam
) const
{
	Debug_Null_Pointer(Curve());
	auto value = Curve()->Value(theParam);
	return std::move(value);
}

AutLib::Pnt2d
AutLib::Pln_Curve::NormalizedParameterValue
(
	const Standard_Real theParam
) const
{
	auto p = FirstParam() + theParam * (LastParam() - FirstParam());
	auto value = Value(p);
	return std::move(value);
}

AutLib::Entity2d_Box
AutLib::Pln_Curve::BoundingBox() const
{
	Debug_Null_Pointer(Curve());
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(Curve(), FirstParam(), LastParam(), 0, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}

//- Static functions and operators

#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

std::shared_ptr<AutLib::Entity2d_Polygon>
AutLib::Pln_Curve::Discretize
(
	const Pln_Curve & theCurve,
	const Standard_Integer theNbSegments
)
{
	const auto& geom = theCurve.Curve();

	auto nbSegmts = theNbSegments;
	if (Handle(Geom2d_Line)::DownCast(geom))
	{
		nbSegmts = 1;
	}
	else
	{
		nbSegmts = MIN(nbSegmts, 5);
	}

	auto poly = std::make_shared<Entity2d_Polygon>();
	auto du = (theCurve.LastParam() - theCurve.FirstParam()) / (Standard_Real)nbSegmts;

	auto& pts = poly->Points();
	pts.reserve(nbSegmts + 1);
	forThose(Index, 0, nbSegmts)
	{
		auto u = Index * du + theCurve.FirstParam();
		pts.push_back(geom->Value(u));
	}

	return std::move(poly);
}

std::shared_ptr<AutLib::Pln_Curve>
AutLib::Pln_Curve::MakeLineSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const std::shared_ptr<info>& theInfo
)
{
	Handle(Geom2d_Curve) geom =
		new Geom2d_Line(theP0, gp_Dir2d(gp_Vec2d(theP0, theP1)));

	Geom2dAPI_ProjectPointOnCurve Projection;

	Projection.Init(theP0, geom);
	auto first = Projection.LowerDistanceParameter();

	Projection.Init(theP1, geom);
	auto last = Projection.LowerDistanceParameter();

	auto curve = std::make_shared<Pln_Curve>(first, last, geom, theInfo);
	return std::move(curve);
}

std::shared_ptr<AutLib::Pln_Curve>
AutLib::Pln_Curve::MakeCircularArc
(
	const gp_Ax22d & A,
	const Standard_Real Radius,
	const Standard_Real theDeg0,
	const Standard_Real theDeg1,
	const std::shared_ptr<info>& theInfo
)
{
	Handle(Geom2d_Curve) geom = new Geom2d_Circle(A, Radius);

	auto first = Processor::DegToRadian(theDeg0);
	auto last = Processor::DegToRadian(theDeg1);

	auto curve = std::make_shared<Pln_Curve>(first, last, geom, theInfo);
	return std::move(curve);
}

std::shared_ptr<AutLib::Pln_Curve>
AutLib::Pln_Curve::MakeCircularArc
(
	const gp_Ax2d & A,
	const Standard_Real Radius,
	const Standard_Real theDeg0,
	const Standard_Real theDeg1,
	const std::shared_ptr<info>& theInfo,
	const Standard_Boolean Sense
)
{
	auto curve = MakeCircularArc(gp_Ax22d(A, Sense), Radius, theDeg0, theDeg1, theInfo);
	return std::move(curve);
}