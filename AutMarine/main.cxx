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
	auto fun = std::make_shared<GeoSizeFun_Uniform<Pnt2d>>(0.2);
	Mesh_AftMetricPrcsr<Aft2d_Edge, GeoSizeFun_Uniform<Pnt2d>> procsr(fun);

	procsr.CalcDistance(Pnt2d(1, 2), Pnt2d(0.1, 9));
	cout << procsr.CalcDistance(Pnt2d(1, 2), Pnt2d(1, 4)) << std::endl;
	PAUSE;
	return 0;
	B<double> bb;
	bb.f(1);

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

	Leg_Nihad2_BareHull patch;
	
	/*patch.AftSection().Tightness0()->SetValue(0.1);
	patch.AftSection().Tightness1()->SetValue(0.1);

	patch.MidSection().Tightness0()->SetValue(0.1);
	patch.MidSection().Tightness1()->SetValue(0.1);*/

	patch.FwdSection().Tightness0()->SetValue(0.9);
	patch.FwdSection().Tightness1()->SetValue(0.9);

	patch.AftSection().Trim()->SetValue(0.1);
	patch.MidSection().Trim()->SetValue(0.1);
	patch.FwdSection().Trim()->SetValue(0.1);


	patch.Perform();
	//patch.Discrete();

	fileName name("preview.plt");
	OFstream myFile(name);

	auto gsurface = patch.Patch();

	//auto preview = Cad_Tools::PreviewPatchCurves(gsurface, 15, 15);

	//preview->ExportToPlt(myFile);

	auto surfaces = TModel_Tools::GetSurfaces(patch.Entity());

	auto solid = Cad3d_TModel::MakeSolid(surfaces, 1.0e-6);

	const auto& faces = solid->Faces();
	faces->Print(Standard_True);

	auto block = faces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(block);

	cout << block->Name() << std::endl;

	block->SelectEntity(1);
	block->SelectEntity(3);

	faces->Split("Block 1");

	faces->Print(Standard_True);

	/*patch.FileFormat() = Leg_EntityIO_Format::IGES;
	patch.ExportToFile();

	auto section = patch.GetStation(5);

	Cad_Tools::ExportToIGES("MM", section, "section.iges");*/

	PAUSE;
	return 0;
}