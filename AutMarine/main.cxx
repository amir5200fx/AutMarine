#include <error.hxx>
#include <OSstream.hxx>

#include <Global_Macros.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <fstream>
#include <iostream>
#include <IO_IGES.hxx>
#include <FastDiscrete_Params.hxx>
#include <Leg_Vessel_Nihad2.hxx>
#include <Cad_Tools.hxx>
#include <Cad3d_TModel.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Tools.hxx>
#include <FastDiscrete.hxx>
#include <Poly_Triangulation.hxx>
#include <Global_Timer.hxx>

#include <Numeric_GaussQuadrature.hxx>
#include <Numeric_IntegrationFunction.hxx>

#include <Geom2d_Circle.hxx>
#include <Geo_CurveLength.hxx>

#include <GeoSizeFun_Uniform.hxx>
#include <Mesh2d_AftMetricPrcsr.hxx>

namespace AutLib
{

	struct IntFun
		: public Numeric_IntegrationFunction
	{

		Standard_Real Value(const Standard_Real x) const override
		{
			cout <<" x = " << x << std::endl;
			return 3*x*x;
		}
	};

	template<class T>
	class A
	{
	public:

		A()
		{}

		void f(int)
		{}
	};

	template<class T>
	class B : public A<T>
	{
	public:

		using A<T>::f;

		B()
		{}

		void f(int ,int)
		{}
	};
}


using namespace boost::archive;
using namespace AutLib;

int main()
{
	/*auto fun = std::make_shared<GeoSizeFun_Uniform<Pnt2d>>(0.2);
	Mesh_AftMetricPrcsr<Aft2d_Edge, GeoSizeFun_Uniform<Pnt2d>> procsr(fun);

	procsr.CalcDistance(Pnt2d(1, 2), Pnt2d(0.1, 9));
	cout << procsr.CalcDistance(Pnt2d(1, 2), Pnt2d(1, 4)) << std::endl;
	PAUSE;
	return 0;
	B<double> bb;
	bb.f(1);*/

	/*IO_IGES reader(gl_fast_discrete_parameters);
	reader.Verbose() = 1;
	reader.ReadFile("F16 one.IGS");*/

	/*IntFun integrand;
	Numeric_GaussQuadrature<IntFun, 4> intg(integrand, 0, 1);
	intg.Perform();

	std::cout << intg.Result() << std::endl;
	PAUSE;
	return 0; */

	/*Numeric_AdaptIntegrationInfo inf;

	Geom2d_Circle circle(gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(1, 0)), 1.0);

	Geo_CurveIntegrand<Geom2d_Circle> integrand(circle);
	cout << "length = " << GeoLib::CalcCurveLength<Geom2d_Circle>::_(integrand, circle.FirstParameter(), circle.LastParameter(), inf);*/

	fileName name("preview.plt");
	OFstream myFile(name);

	{
		Global_Timer timer;

		Leg_Nihad2_BareHull patch;

		/*patch.AftSection().Tightness0()->SetValue(0.1);
		patch.AftSection().Tightness1()->SetValue(0.1);

		patch.MidSection().Tightness0()->SetValue(0.1);
		patch.MidSection().Tightness1()->SetValue(0.1);*/

		/*patch.FwdSection().Tightness0()->SetValue(0.9);
		patch.FwdSection().Tightness1()->SetValue(0.9);*/

		patch.Parameters().SetNbNetColumns(25);

		patch.Parameters().LengthOnDeck()->SetValue(16.0);
		patch.Parameters().TransomHeight()->SetValue(0.6);

		patch.Parameters().FwdFullness()->SetValue(0.5);

		patch.AftSection().Trim0()->SetValue(0.42);
		patch.AftSection().Trim1()->SetValue(0.2);

		patch.MidSection().Trim0()->SetValue(0.45);
		patch.MidSection().Trim1()->SetValue(0.12);

		patch.FwdSection().Trim0()->SetValue(0.35);
		patch.FwdSection().Trim1()->SetValue(0.15);

		patch.Parameters().Position()->SetValue(0.35);
		patch.Parameters().RisePoint()->SetValue(0.15);
		patch.Parameters().RiseSlope()->SetValue(0.05);
		patch.Parameters().TransomSlope()->SetValue(0.37);

		patch.FwdFullness()->SetValue(0.4);
		patch.AftFullness()->SetValue(0.45);

		patch.Parameters().StemRake()->SetValue(30.0);


		patch.Parameters().ForeFootShape()->SetValue(0.65);
		patch.Parameters().BowRounding()->SetValue(0.0);

		patch.PerformToPreview();


		//patch.Discrete();
		patch.FileName() = "myModle.plt";



		/*patch.FileFormat() = Leg_EntityIO_Format::TecPlot;
		patch.ExportToFile();
		PAUSE;
		return 0;*/
		const auto& myShape = patch.PreviewEntity();

		/*auto meshes = Cad_Tools::PreviewUnMergedPatchCurves(myShape, 20, 20);
		for (const auto& x : meshes)
		{
			x->ExportToPlt(myFile);
		}*/

		
	}

	cout << global_time_duration << std::endl;
	PAUSE;
	return 0;

	//auto oriented = myShape.Oriented(TopAbs_FORWARD);
	//auto mySolid = Cad3d_TModel::MakeSolid(myShape, 1.0e-6);


	//FastDiscrete::Triangulation(myShape, *gl_fast_discrete_parameters);

	//auto myTris = Cad_Tools::RetrieveTriangulation(myShape);

	/*for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}*/

	PAUSE;
	return 0;

	//auto gsurface = patch.Entity();


	//auto preview = Cad_Tools::PreviewPatchCurves(gsurface, 15, 15);

	/*for (const auto& x : preview)
	{
		x->ExportToPlt(myFile);
	}*/

	/*auto surfaces = TModel_Tools::GetSurfaces(patch.Entity());

	auto solid = Cad3d_TModel::MakeSolid(surfaces, 1.0e-6);

	std::vector<std::shared_ptr<TModel_Surface>> surfaces1;
	solid->RetrieveFacesTo(surfaces1);

	for (const auto& x : surfaces1)
	{
		const auto& face = x->Face();
		FastDiscrete::Triangulation(face, *gl_fast_discrete_parameters);

		auto tri = Cad_Tools::RetrieveTriangulation(face);
		cout << face.IsNull() << std::endl;
		std::cout << tri.IsNull() << std::endl;
		PAUSE;

		if (tri.IsNull()) continue;

		Cad_Tools::Triangulation(*tri)->ExportToPlt(myFile);
	}
	PAUSE;
	return 0;
	const auto& faces = solid->Faces();
	faces->Print(Standard_True);

	auto block = faces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(block);

	cout << block->Name() << std::endl;

	block->SelectEntity(1);
	block->SelectEntity(3);

	faces->Split("Block 1");

	faces->Print(Standard_True);*/

	/*patch.FileFormat() = Leg_EntityIO_Format::IGES;
	patch.ExportToFile();

	auto section = patch.GetStation(5);

	Cad_Tools::ExportToIGES("MM", section, "section.iges");*/

	PAUSE;
	return 0;
}