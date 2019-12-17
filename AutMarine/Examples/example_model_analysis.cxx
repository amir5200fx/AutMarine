#include <AutMarine_Examples.hxx>

#include <Geo_ApprxCurve_System.hxx>
#include <GeoSizeFun_Uniform.hxx>
#include <CadAnalys_Model_System.hxx>
#include <CadCascade_Box.hxx>
#include <CadCascade_Sphere.hxx>
#include <CadAnalys_tModel.hxx>
#include <Cad_Tools.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Edge.hxx>
#include <Cad3d_TModel.hxx>
#include <FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>

#include <Poly_Triangulation.hxx>

void AutLib::example_model_analysis()
{

	fileName name("preview.plt");
	OFstream myFile(name);

	//auto model = std::make_shared<CadCascade_Box>(Pnt3d(0, 0, 0), Pnt3d(0.1, 0.3, 0.43));
	auto model = std::make_shared<CadCascade_Sphere>(Pnt3d(0, 0, 0), 1.0);

	auto tmodel = Cad3d_TModel::MakeSolid(model->Shape(), 1.0E-6);
	TModel_Tools::DicreteEdges(*tmodel, approxCurveSys::gl_approx_curve3d_info);

	FastDiscrete::Triangulation(model->Shape(), *gl_fast_discrete_parameters);
	

	auto myTris = Cad_Tools::RetrieveTriangulation(model->Shape());

	for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}

	std::vector<std::shared_ptr<TModel_Surface>> surfaces;
	tmodel->RetrieveFacesTo(surfaces);

	auto curves = TModel_Tools::RetrieveEdges(surfaces);

	for (const auto& x : curves)
	{
		if (NOT x->Mesh()) continue;
		x->Mesh()->ExportToPlt(myFile);
	}

	/*auto sizeFun = std::make_shared<GeoSizeFun_Uniform<Pnt3d>>(0.05, tmodel->BoundingBox());

	auto analys = std::make_shared<CadAnalys_tModel>(surfaces, sizeFun, cadAnalysSys::gl_model_analysis_info);
	analys->Perform();*/
}