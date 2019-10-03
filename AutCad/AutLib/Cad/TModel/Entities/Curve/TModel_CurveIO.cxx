#include <TModel_Curve.hxx>

#include <Entity3d_Polygon.hxx>
#include <Cad_CurveInfo.hxx>
#include <TModel_Tools.hxx>
#include <TecPlot.hxx>

void AutLib::TModel_Curve::ExportToPlt(OFstream & File) const
{
	auto poly = TModel_Tools::UniformDiscrete(*this, theInfo_->NbDivisions());
	Io::ExportCurve(poly->Points(), File);
}