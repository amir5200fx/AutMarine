#include <Pln_Curve.hxx>

#include <GeoProcessor.hxx>
#include <Cad_Tools.hxx>

#include <StdFail_NotDone.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>

AutLib::Pln_Curve::Pln_Curve
(
	const Standard_Real theFirst, 
	const Standard_Real theLast,
	const Handle(Geom2d_Curve)& theCurve, 
	const std::shared_ptr<info>& theInfo
)
	: Cad_Curve<Geom2d_Curve>(theFirst, theLast, theCurve)
	, theInfo_(theInfo)
{
	if (NOT Handle(Geom2d_BSplineCurve)::DownCast(theCurve))
	{
		FatalErrorIn("Pln_Curve()")
			<< " the curve is not bspline" << endl
			<< abort(FatalError);
	}
}

AutLib::Pln_Curve::Pln_Curve
(
	const Standard_Integer theIndex, 
	const word& theName, 
	const Standard_Real theFirst,
	const Standard_Real theLast, 
	const Handle(Geom2d_Curve)& theCurve,
	const std::shared_ptr<info>& theInfo
)
	: Cad_Curve<Geom2d_Curve>(theFirst, theLast, theCurve)
	, Pln_Entity(theIndex, theName)
	, theInfo_(theInfo)
{
	if (NOT Handle(Geom2d_BSplineCurve)::DownCast(theCurve))
	{
		FatalErrorIn("Pln_Curve()")
			<< " the curve is not bspline" << endl
			<< abort(FatalError);
	}
}

void AutLib::Pln_Curve::Init
(
	const Standard_Real theFirst, 
	const Standard_Real theLast,
	const Handle(Geom2d_Curve)& theCurve
)
{
	if (NOT Handle(Geom2d_BSplineCurve)::DownCast(theCurve))
	{
		FatalErrorIn("void Init()")
			<< " the curve is not bspline" << endl
			<< abort(FatalError);
	}

	base::SetFirstParam(theFirst);
	base::SetLastParam(theLast);

	base::SetCurve(theCurve);
}

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

Standard_Boolean 
AutLib::Pln_Curve::Interpolation
(
	const std::vector<Pnt2d>& theQ,
	const Standard_Integer theDeg,
	const Standard_Real theTolerance
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("Standard_Boolean AutLib::Plane_Curve::Interpolation(const pointList & theQ, const Standard_Integer theDeg, const Standard_Real theTolerance)")
			<< "Not enough points"
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
	auto& Pts = *PtsPtr;
	forThose(Index, 0, theQ.size() - 1)
		Pts.SetValue(Index + 1, theQ[Index]);

	Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, theTolerance);
	Interpolation.Perform();

	if (!Interpolation.IsDone())
	{
		return Standard_True;
	}

	try
	{
		Init
		(
			Interpolation.Curve()->FirstParameter(),
			Interpolation.Curve()->LastParameter(),
			Interpolation.Curve()
		);
		return Standard_False;
	}
	catch (StdFail_NotDone&)
	{
		return Standard_True;
	}
}

void AutLib::Pln_Curve::Split
(
	const Standard_Real x,
	std::shared_ptr<Pln_Curve>& theLeft,
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Cad_Tools::SplitCurve(Curve(), x, C0, C1);

	theLeft = std::make_shared<Pln_Curve>(C0->FirstParameter(), C0->LastParameter(), C0, Info());
	theRight = std::make_shared<Pln_Curve>(C1->FirstParameter(), C1->LastParameter(), C1, Info());
}

void AutLib::Pln_Curve::Split
(
	const Standard_Real x, 
	Pnt2d & theCoord, 
	std::shared_ptr<Pln_Curve>& theLeft,
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Cad_Tools::SplitCurve(Curve(), x, C0, C1);

	theCoord = Curve()->Value(x);

	theLeft = std::make_shared<Pln_Curve>(C0->FirstParameter(), C0->LastParameter(), C0, Info());
	theRight = std::make_shared<Pln_Curve>(C1->FirstParameter(), C1->LastParameter(), C1, Info());
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
	auto trimmed = Cad_Tools::MakeSegment(theP0, theP1);

	auto curve = 
		std::make_shared<Pln_Curve>
		(
			trimmed->FirstParameter(), 
			trimmed->LastParameter(), trimmed, theInfo);

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

	auto trimmed = Cad_Tools::ConvertToTrimmedCurve(geom, first, last);

	auto curve = std::make_shared<Pln_Curve>(first, last, trimmed, theInfo);
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