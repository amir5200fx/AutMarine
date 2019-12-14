#include <AutMarine_Examples.hxx>

#include <Leg_Vessel_Nihad2.hxx>
#include <Cad3d_TModel.hxx>
#include <FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <TModel_Surface.hxx>
#include <Cad_Tools.hxx>

#include <Poly_Triangulation.hxx>

void AutLib::example_spliting_block_surface()
{
	fileName name("preview.plt");
	OFstream myFile(name);

	Leg_Nihad2_BareHull patch;
	patch.Perform();

	const auto& myShape = patch.Entity();

	auto solid = Cad3d_TModel::MakeSolid(myShape, 1.0E-6);

	auto& surfaces = solid->Faces();
	surfaces->Print(Standard_True);

	auto block = surfaces->SelectBlockEntity("Default Block Surface");
	block->SelectEntity(1);

	surfaces->Split("surf1");

	block = surfaces->SelectBlockEntity("Default Block Surface");
	block->SelectEntity(2);

	surfaces->Split("surf2");

	FastDiscrete::Triangulation(myShape, *gl_fast_discrete_parameters);

	std::vector<std::shared_ptr<Cad_BlockEntity<TModel_Surface>>> blocks;
	surfaces->RetrieveTo(blocks);

	for (const auto& x : blocks)
	{
		std::vector<std::shared_ptr<TModel_Surface>> patches;
		x->RetrieveEntitiesTo(patches);

		cout << patches.size() << std::endl;
		for (const auto& pt : patches)
		{
			const auto& tri = pt->RetrieveTriangulation();

			auto mesh = Cad_Tools::Triangulation(*tri);
			mesh->ExportToPlt(myFile);
		}
	}
}