#include <Cad3d_GModel.hxx>

#include <GModel_Surface.hxx>

void AutLib::Cad3d_GModel::ExportToPlt(OFstream & File) const
{
	for (const auto& x : theSurfaces_)
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}
