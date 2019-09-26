#include <TecPlot_Opencascade.hxx>

#include <Global_Macros.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

#include <Poly_Triangle.hxx>
#include <Poly_Triangulation.hxx>
#include <Geom_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>

void AutLib::Io::ExportMesh
(
	const TColgp_Array1OfPnt & Points,
	const Poly_Array1OfTriangle & Triangles,
	OFstream & File
)
{
	if (!Points.Size()) return;
	if (!Triangles.Size()) return;

	WriteVariables("X Y Z", File);

	WriteFeTriangleZone(Points.Size(), Triangles.Size(), File);

	forThose(Index, Points.Lower(), Points.Upper())
	{
		Pnt3d(Points.Value(Index)).AddToPlt(File);
		File << endl;
	}

	forThose(Index, Triangles.Lower(), Triangles.Upper())
	{
		Standard_Integer I1, I2, I3;

		const auto& triangleIndices = Triangles.Value(Index);
		triangleIndices.Get(I1, I2, I3);

		File << I1 << "  " << I2 << "  " << I3 << endl;
	}
}

void AutLib::Io::ExportMesh
(
	const Poly_Triangulation & Triangulation,
	OFstream & File
)
{
	ExportMesh(Triangulation.Nodes(), Triangulation.Triangles(), File);
}

void AutLib::Io::ExportCurve
(
	const Geom_Curve & Curve,
	const Standard_Real First,
	const Standard_Real Last,
	const Standard_Integer NbSegmets,
	OFstream & File
)
{
	Standard_Integer Nb = MAX(1, NbSegmets);

	std::vector<Pnt3d> Points(Nb + 1);
	Standard_Real Du = (Last - First) / (Standard_Real)(Nb);

	Curve.D0(First, Points[0]);
	forThose(Index, 1, Nb - 1)
	{
		Standard_Real Parameter = (Standard_Real)Index*Du + First;

		Curve.D0(Parameter, Points[Index]);
	}
	Curve.D0(Last, Points[Nb]);

	ExportCurve(Points, File);
}

void AutLib::Io::ExportCurve
(
	const Geom2d_Curve & Curve,
	const Standard_Real First,
	const Standard_Real Last,
	const Standard_Integer NbSegmets,
	OFstream & File
)
{
	Standard_Integer Nb = MAX(1, NbSegmets);

	std::vector<Pnt2d> Points(Nb + 1);
	Standard_Real Du = (Last - First) / (Standard_Real)(Nb);

	Curve.D0(First, Points[0]);
	forThose(Index, 1, Nb - 1)
	{
		Standard_Real Parameter = (Standard_Real)Index*Du + First;

		Curve.D0(Parameter, Points[Index]);
	}
	Curve.D0(Last, Points[Nb]);

	ExportCurve(Points, File);
}

void AutLib::Io::ExportCurve
(
	const TopoDS_Edge & Curve,
	const Standard_Integer NbSegmets,
	OFstream & File
)
{
	Standard_Real First, Last;
	Handle(Geom_Curve) gm_Curve = BRep_Tool::Curve(Curve, First, Last);

	if (NOT gm_Curve) return;

	ExportCurve(*gm_Curve, First, Last, NbSegmets, File);
}

void AutLib::Io::ExportCurvesOf
(
	const TopoDS_Shape & theShape,
	const Standard_Integer nbSegments,
	OFstream & File
)
{
	TopExp_Explorer anEdgeExplorer;
	anEdgeExplorer.Init(theShape, TopAbs_EDGE);

	while (anEdgeExplorer.More())
	{
		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
		ExportCurve(anEdge, nbSegments, File);

		anEdgeExplorer.Next();
	}
}