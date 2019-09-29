#include <TModel_parCurve.hxx>

#include <Entity2d_Box.hxx>
#include <error.hxx>
#include <OSstream.hxx>

//- OpenCascade library
#include <Geom2d_Curve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dConvert.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>

Standard_Boolean
AutLib::TModel_parCurve::IsClosed
(
	const Standard_Real theTol
) const
{
	return SquareDistance(Start(), Last()) <= theTol * theTol;
}

AutLib::Pnt2d
AutLib::TModel_parCurve::Start() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Value(FirstParam());
}

AutLib::Pnt2d
AutLib::TModel_parCurve::Last() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Value(LastParam());
}

AutLib::Pnt2d
AutLib::TModel_parCurve::Value
(
	const Standard_Real x
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("Pnt2d TModel_parCurve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}
	return Curve()->Value(x);
}

AutLib::Pnt2d
AutLib::TModel_parCurve::NormalizedParameterValue
(
	const Standard_Real x
) const
{
	if (NOT INSIDE(x, 0, 1))
	{
		FatalErrorIn("Pnt2d TModel_parCurve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << 0 << endl
			<< " - Last Parameter: " << 1 << endl
			<< abort(FatalError);
	}
	return Curve()->Value(FirstParam() + x * (LastParam() - FirstParam()));
}

AutLib::Entity2d_Box
AutLib::TModel_parCurve::BoundingBox
(
	const Standard_Real theTol
) const
{
	Debug_Null_Pointer(Curve());
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(Curve(), FirstParam(), LastParam(), theTol, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}

void AutLib::TModel_parCurve::ReverseGeometry()
{
	Debug_Null_Pointer(Curve());
	Curve()->Reverse();

	auto temp = LastParam();
	LastParam() = Curve()->ReversedParameter(FirstParam());
	FirstParam() = Curve()->ReversedParameter(temp);
}

void AutLib::TModel_parCurve::Split
(
	const Standard_Real x,
	std::shared_ptr<TModel_parCurve>& theC1,
	std::shared_ptr<TModel_parCurve>& theC2
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("void Split(const Standard_Real x, pCurve_ptr& theC1, pCurve_ptr& theC2, const Standard_Real theTol) const")
			<< "The Parameter is out of valid range: " << x << endl
			<< " - First parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}

	theC1 = std::make_shared<TModel_parCurve>(FirstParam(), x, Curve(), Info());
	theC2 = std::make_shared<TModel_parCurve>(x, LastParam(), Curve(), Info());
}

void AutLib::TModel_parCurve::BSplineSplit
(
	const Standard_Real x,
	std::shared_ptr<TModel_parCurve>& theC1,
	std::shared_ptr<TModel_parCurve>& theC2
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("void BSplineSplit(const Standard_Real x, pCurve_ptr& theC1, pCurve_ptr& theC2, const Standard_Real theTol) const")
			<< "The Parameter is out of valid range: " << x << endl
			<< " - First parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}

	auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(Curve());
	if (NOT bspline)
	{
		Handle(Geom2d_TrimmedCurve) trimmed = new Geom2d_TrimmedCurve(Curve(), FirstParam(), LastParam());
		bspline = Geom2dConvert::CurveToBSplineCurve(trimmed);
	}

	Handle(Geom2d_TrimmedCurve) trimmed0 =
		new Geom2d_TrimmedCurve(bspline, bspline->FirstParameter(), x);
	Handle(Geom2d_TrimmedCurve) trimmed1 =
		new Geom2d_TrimmedCurve(bspline, x, bspline->LastParameter());

	auto left = Geom2dConvert::CurveToBSplineCurve(trimmed0);
	auto right = Geom2dConvert::CurveToBSplineCurve(trimmed1);

	theC1 = std::make_shared<TModel_parCurve>(left->FirstParameter(), left->LastParameter(), left, Info());
	theC2 = std::make_shared<TModel_parCurve>(right->FirstParameter(), right->LastParameter(), right, Info());
}

AutLib::TModel_parCurve::curveList
AutLib::TModel_parCurve::Split
(
	const std::list<Standard_Real>& theParams,
	const Standard_Real theTol
) const
{
	auto first = FirstParam();
	auto last = LastParam();
	auto curve = const_cast<TModel_parCurve*>(this);

	pCurve_ptr rightCurve;
	curveList curves;

	for (const auto x : theParams)
	{
		if (ABS(x - first) <= theTol OR ABS(x - last) <= theTol)
		{
			continue;
		}

		pCurve_ptr leftCurve;
		curve->Split(x, leftCurve, rightCurve);

		Debug_Null_Pointer(leftCurve);
		Debug_Null_Pointer(rightCurve);

		curves.push_back(leftCurve);

		curve = rightCurve.get();
	}

	if (curves.size())
	{
		Debug_Null_Pointer(rightCurve);
		curves.push_back(rightCurve);
	}
	return std::move(curves);
}

AutLib::TModel_parCurve::curveList
AutLib::TModel_parCurve::BSplineSplit
(
	const std::list<Standard_Real>& theParams,
	const Standard_Real theTol
) const
{
	auto first = FirstParam();
	auto last = LastParam();
	auto curve = const_cast<TModel_parCurve*>(this);

	pCurve_ptr rightCurve;
	curveList curves;

	for (const auto x : theParams)
	{
		if (ABS(x - first) <= theTol OR ABS(x - last) <= theTol)
		{
			continue;
		}

		pCurve_ptr leftCurve;
		curve->BSplineSplit(x, leftCurve, rightCurve);

		Debug_Null_Pointer(leftCurve);
		Debug_Null_Pointer(rightCurve);

		curves.push_back(leftCurve);

		curve = rightCurve.get();
	}

	if (curves.size())
	{
		Debug_Null_Pointer(rightCurve);
		curves.push_back(rightCurve);
	}
	return std::move(curves);
}