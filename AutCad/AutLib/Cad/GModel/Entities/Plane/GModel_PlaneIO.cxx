#include <GModel_Plane.hxx>

#include <GModel_parWire.hxx>

void AutLib::GModel_Plane::ExportToPlt(OFstream & File) const
{
	if (theOutter_)
	{
		theOutter_->ExportToPlt(File);
	}

	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			Debug_Null_Pointer(x);
			x->ExportToPlt(File);
		}
	}
}