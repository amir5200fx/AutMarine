#include <TModel_Edge.hxx>

#include <Entity3d_Chain.hxx>
#include <Entity3d_Polygon.hxx>
#include <Geo3d_ApprxCurve.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Curve.hxx>
#include <Geo_ApprxCurveInfo.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom_Curve.hxx>

void AutLib::TModel_Edge::Discrete(const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo) const
{
	const auto& geom = Geometry();

	auto alg = std::make_shared<Geo3d_ApprxCurve>();
	Debug_Null_Pointer(alg);

	alg->LoadCurve(geom->Curve(), geom->FirstParam(), geom->LastParam(), theInfo);
	alg->Perform();

	ChangeMesh() = alg->Chain();
}

//- Static functions and operators

//std::shared_ptr<AutLib::Entity3d_Chain> 
//AutLib::TModel_Edge::GetStatic
//(
//	const TModel_Edge & theEdge
//)
//{
//	auto chain = std::make_shared<Entity3d_Chain>();
//	Debug_Null_Pointer(chain);
//
//	auto& pts = chain->Points();
//	pts.reserve(2);
//
//	pts.push_back(theEdge.Vtx0()->Coord());
//	pts.push_back(theEdge.Vtx1()->Coord());
//
//	auto& indices = chain->Connectivity();
//	indices.reserve(1);
//
//	connectivity::dual I;
//	I.Value(0) = 1;
//	I.Value(1) = 2;
//
//	indices.push_back(std::move(I));
//
//	return std::move(chain);
//}