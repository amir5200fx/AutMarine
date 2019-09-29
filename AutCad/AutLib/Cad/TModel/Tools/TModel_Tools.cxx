#include <TModel_Tools.hxx>

#include <TModel_Surface.hxx>
#include <TModel_Edge.hxx>
#include <error.hxx>
#include <OSstream.hxx>

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