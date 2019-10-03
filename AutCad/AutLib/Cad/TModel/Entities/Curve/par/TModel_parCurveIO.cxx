#include <TModel_parCurve.hxx>

#include <Cad_CurveInfo.hxx>
#include <Entity2d_Polygon.hxx>
#include <TModel_Tools.hxx>
#include <TecPlot.hxx>

void AutLib::TModel_parCurve::ExportToPlt(OFstream & File) const
{
	auto poly = TModel_Tools::UniformDiscrete(*this, theInfo_->NbDivisions());
	Io::ExportCurve(poly->Points(), File);
}