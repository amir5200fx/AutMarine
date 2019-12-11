#include <AutMarine_Examples.hxx>

#include <Cad_Tools.hxx>
#include <FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <IO_IGES.hxx>
#include <Cad3d_GModel.hxx>

#include <Poly_Triangulation.hxx>

void AutLib::example_reading_iges_creating_gmodel()
{
	auto params = std::make_shared<FastDiscrete_Params>();
	params->Deflection = 0.5;
	params->Angle = 2.0;

	params->InParallel = Standard_True;

	IO_IGES reader(params);
	reader.SetVerbisity(1);
	reader.ReadFile("F16 one.IGS");

	auto model = Cad3d_GModel::GModel(reader.Shape());

	fileName name("preview.plt");
	OFstream myFile(name);

	FastDiscrete::Triangulation(reader.Shape(), *params);

	auto myTris = Cad_Tools::RetrieveTriangulation(reader.Shape());

	for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}

	PAUSE;
}