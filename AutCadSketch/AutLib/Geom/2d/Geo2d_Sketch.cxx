#include <Geo2d_Sketch.hxx>

#include <Pnt2d.hxx>
#include <Geom2d_Curve.hxx>
#include <TecPlot.hxx>

#include <vector>

void AutLib::Geo2d_Sketch::ExportToPlt(OFstream & File) const
{
	auto first = Geometry()->FirstParameter();
	auto last = Geometry()->LastParameter();

	const Standard_Integer nbSegments = 20;
	auto du = (last - first) / (Standard_Real)nbSegments;

	std::vector<Pnt2d> Pts;
	Pts.reserve(nbSegments + 1);

	forThose(Index, 0, nbSegments)
	{
		auto u = first + Index * du;
		Pts.push_back(Geometry()->Value(u));
	}

	Io::ExportCurve(Pts, File);
}