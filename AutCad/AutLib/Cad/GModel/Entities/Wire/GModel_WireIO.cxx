#include <GModel_Wire.hxx>

#include <GModel_parCurve.hxx>

void AutLib::GModel_Wire::ExportPlaneCurvesToPlt(OFstream & File) const
{
	auto curves = RetrievePlaneCurves(*this);
	Debug_Null_Pointer(curves);

	for (const auto& x : *curves)
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}