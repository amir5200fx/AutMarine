#include <Cad3d_TModel.hxx>

#include <Pnt3d.hxx>
#include <Entity3d_Polygon.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Surface.hxx>
#include <TecPlot.hxx>

void AutLib::Cad3d_TModel::ExportCornersToPlt
(
	OFstream & File
) const
{
	if (NOT theVertices_)
	{
		return;
	}

	std::vector<std::shared_ptr<TModel_Vertex>> vertices;
	RetrieveCornersTo(vertices);

	std::vector<Pnt3d> Pts;
	Pts.reserve(vertices.size());
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		Pts.push_back(x->Coord());
	}

	Io::ExportPoints(Pts, File);
}

void AutLib::Cad3d_TModel::ExportSegmentsToPlt
(
	OFstream & File
) const
{
	if (NOT theEdges_)
	{
		return;
	}

	std::vector<std::shared_ptr<TModel_Paired>> edges;
	RetrieveSegmentsTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		if (x->Mesh())
		{
			x->Mesh()->ExportToPlt(File);
		}
	}
}

void AutLib::Cad3d_TModel::ExportFacesToPlt
(
	OFstream & File
) const
{
	if (NOT theSurfaces_)
	{
		return;
	}

	std::vector<std::shared_ptr<TModel_Surface>> surfaces;
	RetrieveFacesTo(surfaces);

	for (const auto& x : surfaces)
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}

void AutLib::Cad3d_TModel::ExportFreeSegmentsToPlt
(
	OFstream & File
) const
{
	if (NOT theEdges_)
	{
		return;
	}

	std::vector<std::shared_ptr<TModel_Paired>> edges;
	RetrieveSegmentsTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		
		if (NOT x->IsPaired())
		{
			if (x->Mesh())
			{
				x->Mesh()->ExportToPlt(File);
			}
		}
	}
}