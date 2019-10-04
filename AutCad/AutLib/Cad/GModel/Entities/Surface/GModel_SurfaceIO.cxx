#include <GModel_Surface.hxx>

#include <Cad_Tools.hxx>
#include <GModel_Wire.hxx>
#include <TecPlot.hxx>

#include <Poly_Triangulation.hxx>

void AutLib::GModel_Surface::ExportPlaneCurvesToPlt(OFstream & File) const
{
	if (theOuter_)
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

void AutLib::GModel_Surface::ExportToPlt(OFstream & File) const
{
	if (theTriangulation_)
	{
		auto triangulation = Cad_Tools::Triangulation(*theTriangulation_);
		Debug_Null_Pointer(triangulation);

		Io::ExportMesh(triangulation->Points(), triangulation->Connectivity(), File);
	}
}