#include <CadPlnModel_Segment.hxx>

#include <Dir2d.hxx>
#include <Pln_Curve.hxx>
#include <Cad_CurveInfo.hxx>
#include <Cad_Tools.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

void AutLib::CadPlnModel_Segment::Make
(
	const Pnt2d& theP0,
	const Pnt2d& theP1,
	const std::shared_ptr<Cad_CurveInfo>& theInfo
)
{
	Dir2d dir(theP0, theP1);
	
	Handle(Geom2d_Line) geom = new Geom2d_Line(theP0, dir);

	Geom2dAPI_ProjectPointOnCurve Projection;

	Projection.Init(theP0, geom);
	auto first = Projection.LowerDistanceParameter();

	Projection.Init(theP1, geom);
	auto last = Projection.LowerDistanceParameter();

	auto bounded = Cad_Tools::ConvertToTrimmedCurve(geom, first, last);
	auto bspline = Cad_Tools::ConvertToBSpline(bounded);

	ChangeEntity() = std::make_shared<Pln_Curve>(first, last, bspline, theInfo);
}

AutLib::CadPlnModel_Segment::CadPlnModel_Segment
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1, 
	const std::shared_ptr<Cad_CurveInfo>& theInfo
)
{
	Make(theP0, theP1, theInfo);
}

AutLib::CadPlnModel_Segment::CadPlnModel_Segment
(
	const gp_Ax22d& theP0,
	const Standard_Real theLength,
	const std::shared_ptr<Cad_CurveInfo>& theInfo
)
{
	const auto& dir = theP0.XAxis().Direction();
	const auto& p0 = theP0.Location();

	const auto p1 = p0 + Pnt2d(dir.X(), dir.Y());

	Make(p0, p1, theInfo);
}

std::shared_ptr<AutLib::Pln_Curve> 
AutLib::CadPlnModel_Segment::operator()
(
	const Pnt2d& theP0,
	const Pnt2d& theP1, 
	const std::shared_ptr<Cad_CurveInfo>& theInfo
	)
{
	CadPlnModel_Segment l(theP0, theP1, theInfo);
	auto curve = l.Curve();
	return std::move(curve);
}

std::shared_ptr<AutLib::Pln_Curve>
AutLib::CadPlnModel_Segment::operator()
(
	const gp_Ax22d& theP0, 
	const Standard_Real theLength, 
	const std::shared_ptr<Cad_CurveInfo>& theInfo
	)
{
	CadPlnModel_Segment l(theP0, theLength, theInfo);
	auto curve = l.Curve();
	return std::move(curve);
}

void AutLib::CadPlnModel_Segment::Discrete
(
	const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
) const
{
	auto chain = std::make_shared<Entity2d_Chain>();

	auto& Pts = chain->Points();
	auto& Indices = chain->Connectivity();

	Pts.resize(2);
	Indices.resize(1);

	Pts[0] = P0();
	Pts[1] = P1();

	Indices[0].Value(0) = 1;
	Indices[0].Value(1) = 2;

	SetMesh(chain);
}