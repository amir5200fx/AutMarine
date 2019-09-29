#include <TModel_Curve.hxx>

#include <Entity3d_Box.hxx>
#include <Cad_CurveInfo.hxx>

#include <Bnd_Box.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_Curve.hxx>

Standard_Boolean 
AutLib::TModel_Curve::IsClosed
(
	const Standard_Real theTol
) const
{
	return SquareDistance(Start(), Last()) <= theTol * theTol;
}

AutLib::Pnt3d
AutLib::TModel_Curve::Start() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Value(FirstParam());
}

AutLib::Pnt3d
AutLib::TModel_Curve::Last() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Value(LastParam());
}

AutLib::Pnt3d
AutLib::TModel_Curve::Value
(
	const Standard_Real x
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("Pnt3d TModel_Curve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}
	return Curve()->Value(x);
}

AutLib::Pnt3d
AutLib::TModel_Curve::NormalizedParameterValue
(
	const Standard_Real x
) const
{
	if (NOT INSIDE(x, 0, 1))
	{
		FatalErrorIn("Pnt3d TModel_Curve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << 0 << endl
			<< " - Last Parameter: " << 1 << endl
			<< abort(FatalError);
	}
	return Curve()->Value(FirstParam() + x * (LastParam() - FirstParam()));
}

AutLib::Entity3d_Box
AutLib::TModel_Curve::BoundingBox
(
	const Standard_Real theTol
) const
{
	Bnd_Box BndBox;
	BndLib_Add3dCurve::Add
	(
		GeomAdaptor_Curve(Curve()),
		FirstParam(),
		LastParam(),
		theTol,
		BndBox
	);

	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	BndBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	Entity3d_Box box(Pnt3d(Xmin, Ymin, Zmin), Pnt3d(Xmax, Ymax, Zmax));
	return std::move(box);
}

void AutLib::TModel_Curve::Split
(
	const Standard_Real x,
	std::shared_ptr<TModel_Curve>& theC1,
	std::shared_ptr<TModel_Curve>& theC2
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

	theC1 = std::make_shared<TModel_Curve>(FirstParam(), x, Curve(), Info());
	theC2 = std::make_shared<TModel_Curve>(x, LastParam(), Curve(), Info());
}