#include <GModel_parCurve.hxx>

#include <Entity2d_Polygon.hxx>
#include <Cad_CurveInfo.hxx>
#include <GModel_Tools.hxx>
#include <TecPlot.hxx>

void AutLib::GModel_parCurve::ExportToPlt(OFstream & File) const
{
	auto poly = GModel_Tools::UniformDiscrete(*this, theInfo_->NbDivisions());
	Io::ExportCurve(poly->Points(), File);
}