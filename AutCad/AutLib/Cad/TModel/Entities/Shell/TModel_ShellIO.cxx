#include <TModel_Shell.hxx>

#include <TModel_Surface.hxx>

void AutLib::TModel_Shell::ExportToPlt(OFstream & File) const
{
	if (theSurfaces_)
	{
		for (const auto& x : *theSurfaces_)
		{
			Debug_Null_Pointer(x);
			x->ExportToPlt(File);
		}
	}
}