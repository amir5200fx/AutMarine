#include <TModel_Plane.hxx>

#include <Global_Macros.hxx>
#include <TModel_parWire.hxx>

void AutLib::TModel_Plane::ExportToPlt(OFstream & File) const
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