#include <Mesh_PlnCurve.hxx>

#include <Geo2d_ApprxCurve.hxx>

std::shared_ptr<AutLib::Entity2d_Chain> 
AutLib::Mesh_PlnCurve_Base::Discrete
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1, 
	const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
)
{
	Geo2d_ApprxCurve Alg(theCurve, theU0, theU1, theInfo);

	Alg.Perform();
	Debug_If_Condition_Message(NOT Alg.IsDone(), "the algorithm has not been performed!");

	auto mesh = Alg.Chain();
	return std::move(mesh);
}
