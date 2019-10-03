#include <GModel_Curve.hxx>

#include <Entity3d_Polygon.hxx>
#include <Cad_CurveInfo.hxx>
#include <GModel_Tools.hxx>
#include <TecPlot.hxx>

//- Io functions and operators

void AutLib::GModel_Curve::ExportToPlt(OFstream & File) const
{
	auto poly = GModel_Tools::UniformDiscrete(*this, theInfo_->NbDivisions());
	Io::ExportCurve(poly->Points(), File);
}