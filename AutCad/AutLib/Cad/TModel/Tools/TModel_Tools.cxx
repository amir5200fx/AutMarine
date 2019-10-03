#include <TModel_Tools.hxx>

#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Edge.hxx>
#include <TModel_Curve.hxx>
#include <TModel_parCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

std::shared_ptr<AutLib::Entity2d_Polygon> 
AutLib::TModel_Tools::UniformDiscrete
(
	const TModel_parCurve & theCurve, 
	const Standard_Integer theNbSegments
)
{
	auto nbSeg = MIN(theNbSegments, 3);

	auto poly = std::make_shared<Entity2d_Polygon>();
	auto& pts = poly->Points();

	pts.reserve(nbSeg + 1);
	auto du = (theCurve.LastParam() - theCurve.FirstParam()) / (Standard_Real)nbSeg;
	auto u0 = theCurve.FirstParam();

	forThose(Index, 0, nbSeg)
	{
		auto u = Index * du + u0;
		pts.push_back(theCurve.Value(u));
	}

	return std::move(poly);
}

std::shared_ptr<AutLib::Entity3d_Polygon> 
AutLib::TModel_Tools::UniformDiscrete
(
	const TModel_Curve& theCurve,
	const Standard_Integer theNbSegments
)
{
	auto nbSeg = MIN(theNbSegments, 3);

	auto poly = std::make_shared<Entity3d_Polygon>();
	auto& pts = poly->Points();

	pts.reserve(nbSeg + 1);
	auto du = (theCurve.LastParam() - theCurve.FirstParam()) / (Standard_Real)nbSeg;
	auto u0 = theCurve.FirstParam();
	
	forThose(Index, 0, nbSeg)
	{
		auto u = Index * du + u0;
		pts.push_back(theCurve.Value(u));
	}

	return std::move(poly);
}

std::vector<std::shared_ptr<AutLib::TModel_Edge>> 
AutLib::TModel_Tools::RetrieveEdges
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	std::vector<std::shared_ptr<AutLib::TModel_Edge>> QEdges;
	for (const auto& x : theSurfaces)
	{
		Debug_Null_Pointer(x);
		const auto& face = *x;

		const auto edges = face.Edges();

		for (const auto& edge : edges)
		{
			QEdges.push_back(edge);
		}
	}
	return std::move(QEdges);
}

std::vector<std::shared_ptr<AutLib::TModel_Edge>> 
AutLib::TModel_Tools::RetrieveNonSingularEdges
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	std::vector<std::shared_ptr<TModel_Edge>> gedges;
	for (const auto& x : theSurfaces)
	{
		Debug_Null_Pointer(x);
		const auto& face = *x;

		const auto edges = face.Edges();
		for (const auto& edge : edges)
		{
			Debug_Null_Pointer(edge);
			if (NOT edge->IsDegenerated())
			{
				gedges.push_back(edge);
			}
		}
	}
	return std::move(gedges);
}