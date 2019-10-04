#include <TModel_Surface.hxx>

#include <Entity3d_Triangulation.hxx>
#include <Cad_Tools.hxx>
#include <TModel_Wire.hxx>

#include <Poly_Triangulation.hxx>

void AutLib::TModel_Surface::ExportPlaneCurvesToPlt(OFstream & File) const
{
	if(theOuter_)
	{
		theOuter_->ExportPlaneCurvesToPlt(File);
	}

	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			Debug_Null_Pointer(x);
			x->ExportPlaneCurvesToPlt(File);
		}
	}
}

void AutLib::TModel_Surface::ExportToPlt(OFstream & File) const
{
	if (NOT theTriangulation_)
	{
		return;
	}

	auto triangulation = Cad_Tools::Triangulation(*theTriangulation_);
	if (triangulation)
	{
		triangulation->ExportToPlt(File);
	}
}