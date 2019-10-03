#include <TModel_Paired.hxx>

#include <TecPlot.hxx>
#include <Entity3d_Polygon.hxx>

void AutLib::TModel_Paired::ExportToPlt(OFstream & File) const
{
	if (NOT Mesh())
	{
		return;
	}

	const auto mesh = *Mesh();
	Io::ExportCurve(mesh.Points(), File);
}