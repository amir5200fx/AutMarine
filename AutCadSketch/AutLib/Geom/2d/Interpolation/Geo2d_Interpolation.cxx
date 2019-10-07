#include <Geo2d_Interpolation.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
//#include <Geom2dAPI_PointsToBSpline.hxx>

#include <Geo2d_InterpolationInfo.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void AutLib::Geo2d_Interpolation::Perform
(
	const std::shared_ptr<Geo2d_InterpolationInfo>& theInfo
)
{
	if (thePts_.size() < 3)
	{
		FatalErrorIn("void Perform()")
			<< "Not enough offset points" << endl
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) Q = new TColgp_HArray1OfPnt2d(1, thePts_.size());
	forThose(Index, 0, thePts_.size() - 1)
	{
		Q->SetValue(Index + 1, thePts_[Index]);
	}

	Geom2dAPI_Interpolate interp(Q, theInfo->PeriodicFlag(), theInfo->Tolerance());
	interp.Perform();

	const auto& curve = interp.Curve();

	ChangeGeometry() = 
		new Geom2d_TrimmedCurve
		(
			curve,
			curve->FirstParameter(),
			curve->LastParameter()
		);

	Change_IsDone() = Standard_True;
}

void AutLib::Geo2d_Interpolation::Perform
(
	const std::shared_ptr<Geo2d_InterpolationInfo>& theInfo, 
	const Vec2d & theFirst,
	const Vec2d & theLast, 
	const Standard_Boolean Scale
)
{
	if (thePts_.size() < 3)
	{
		FatalErrorIn("void Perform()")
			<< "Not enough offset points" << endl
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) Q = new TColgp_HArray1OfPnt2d(1, thePts_.size());
	forThose(Index, 0, thePts_.size() - 1)
	{
		Q->SetValue(Index + 1, thePts_[Index]);
	}

	Geom2dAPI_Interpolate interp(Q, theInfo->PeriodicFlag(), theInfo->Tolerance());

	interp.Load(theFirst, theLast, Scale);
	interp.Perform();

	const auto& curve = interp.Curve();

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			curve,
			curve->FirstParameter(),
			curve->LastParameter()
		);

	Change_IsDone() = Standard_True;
}