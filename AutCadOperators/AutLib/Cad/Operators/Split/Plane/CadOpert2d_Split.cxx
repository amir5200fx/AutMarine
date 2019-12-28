#include <CadOpert2d_Split.hxx>

#include <Entity2d_Box.hxx>
#include <Geo_BinSearch.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Cad2d_Plane.hxx>
#include <CadOpert2d_IntsctPair.hxx>
#include <CadOpert2d_IntsctTools.hxx>
#include <CadOpert2d_EdgeEdgeIntsct.hxx>
#include <CadOpert2d_EdgeEdgeIntsct_Info.hxx>
#include <CadOpert2d_IntsctCutter_TangClamped.hxx>
#include <CadOpert2d_IntsctCutter_OrthClamped.hxx>
#include <CadOpert2d_IntsctCutter_Dangle.hxx>
#include <CadOpert2d_IntsctSubEdge_Orth.hxx>
#include <CadOpert2d_IntsctSubEdge_Tang.hxx>

namespace AutLib
{
	typedef std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>>
		entList;
}

void AutLib::CadOpert2d_Split::Perform()
{
	if (NOT Edge())
	{
		FatalErrorIn("void Perform()")
			<< "the cutter has not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Shape())
	{
		FatalErrorIn("void Perform()")
			<< " the shape has not been loaded!" << endl
			<< abort(FatalError);
	}

	auto box = Shape()->BoundingBox();

	Geo_BinSearch<Pln_Edge> engine(box.OffSet(1.0E-6*box.Diameter()));

	std::vector<std::shared_ptr<Pln_Edge>> plnEdges;
	Shape()->RetrieveEdgesTo(plnEdges);

	engine.Register(plnEdges);

	std::map<Standard_Integer, std::shared_ptr<entList>> regIntsct0;
	std::map<Standard_Integer, std::shared_ptr<entList>> regIntsct1;

	for (const auto& x : Edge()->Edges())
	{
		Debug_Null_Pointer(x);
		regIntsct0.insert(std::make_pair(x->Index(), std::make_shared<entList>()));
	}

	for (const auto& x : plnEdges)
	{
		Debug_Null_Pointer(x);
		regIntsct0.insert(std::make_pair(x->Index(), std::make_shared<entList>()));
	}

	for (const auto& x : Edge()->Edges())
	{
		Debug_Null_Pointer(x);

		auto b = x->Curve()->BoundingBox();
		auto items = engine.Search(b);

		for (const auto& i : items)
		{
			Debug_Null_Pointer(i);

			auto opt = std::make_shared<CadOpert2d_EdgeEdgeIntsct>(x, i, Info());
			Debug_Null_Pointer(opt);

			opt->Perform();

			Debug_If_Condition_Message(NOT opt->IsDone(), "the intersection algorithm is not performed!");

			if (NOT opt->HasIntersection()) continue;

			auto entities = opt->Entities();

			std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>> entities0;
			std::vector<std::shared_ptr<CadOpert2d_IntsctEntity>> entities1;
			CadOpert2d_IntsctTools::SplitEntities(entities, entities0, entities1);

			for (const auto& ent : entities0)
			{
				Debug_Null_Pointer(ent);
				auto iter = regIntsct0.find(x->Index());

				if (iter IS_EQUAL regIntsct0.end())
				{
					FatalErrorIn("void perform()")
						<< "unable to find the item at the map" << endl
						<< abort(FatalError);
				}

				iter->second->push_back(ent);
			}
			
			for (const auto& ent : entities1)
			{
				Debug_Null_Pointer(ent);
				auto iter = regIntsct1.find(i->Index());

				if (iter IS_EQUAL regIntsct1.end())
				{
					FatalErrorIn("void perform()")
						<< "unable to find the item at the map" << endl
						<< abort(FatalError);
				}

				iter->second->push_back(ent);
			}
		}
	}

	Standard_Boolean Intersection = Standard_False;
	for (const auto& x : regIntsct0)
	{
		Debug_Null_Pointer(x.second);
		if (x.second->size())
		{
			Intersection = Standard_True;
			break;
		}
	}

	if (NOT Intersection)
	{
		Change_IsDone() = Standard_True;
		return;
	}

	for (const auto& x : regIntsct0)
	{
		Debug_Null_Pointer(x.second);

		if (x.second->empty())
		{
			continue;
		}

		if (x.second->size() > 1)
		{
			CadOpert2d_IntsctTools::Sort(*x.second);
		}
	}

	for (const auto& x : regIntsct1)
	{
		Debug_Null_Pointer(x.second);

		if (x.second->empty())
		{
			continue;
		}

		if (x.second->size() > 1)
		{
			CadOpert2d_IntsctTools::Sort(*x.second);
		}
	}

	auto newCutter = CadOpert2d_IntsctTools::SubdivideCmpEdge(*Edge(), regIntsct0);
	auto newPlane = CadOpert2d_IntsctTools::SubdividePlane(*Shape(), regIntsct1);
}