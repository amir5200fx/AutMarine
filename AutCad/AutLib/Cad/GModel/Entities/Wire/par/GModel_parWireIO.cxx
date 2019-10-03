#include <GModel_parWire.hxx>

#include <GModel_parCurve.hxx>

void AutLib::GModel_parWire::ExportToPlt
(
	OFstream & File
) const
{
	if (NOT theCurves_)
	{
		return;
	}

	for (const auto& x : *theCurves_)
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}