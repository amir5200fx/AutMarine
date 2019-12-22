#include <AutMarine_Examples.hxx>

#include <Cad_Tools.hxx>
#include <FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <IO_IGES.hxx>
#include <Cad3d_GModel.hxx>
#include <Cad3d_TModel.hxx>

#include <Poly_Triangulation.hxx>

void AutLib::example_reading_iges_creating_gmodel()
{
	auto params = std::make_shared<FastDiscrete_Params>();
	

	params->InParallel = Standard_True;
	IO_IGES reader(params);
	reader.SetVerbisity(1);

	reader.ReadFile("Sukhoi SU-57 Sokol.igs");

	auto model = Cad3d_TModel::MakeSolid(reader.Shape(), 1.0e-6);

	fileName name("preview.plt");
	OFstream myFile(name);

	params->Deflection = 1.0E-4*model->BoundingBox().Diameter();
	params->Angle = 2.5;
	FastDiscrete::Triangulation(reader.Shape(), *params);

	auto myTris = Cad_Tools::RetrieveTriangulation(reader.Shape());

	for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}
}