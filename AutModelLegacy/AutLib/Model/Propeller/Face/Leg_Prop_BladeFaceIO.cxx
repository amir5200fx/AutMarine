#include <Leg_Prop_BladeFace.hxx>

#include <Cad_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Leg_Model_Surface.hxx>

void AutLib::Leg_Prop_BladeFace::ExportToPlt(OFstream & File) const
{
	auto tri0 = Cad_Tools::Triangulation(Face(), 30, 30);
	auto tri1 = Cad_Tools::Triangulation(Back(), 30, 30);

	Debug_Null_Pointer(tri0);
	Debug_Null_Pointer(tri1);

	tri0->ExportToPlt(File);
	tri1->ExportToPlt(File);
}