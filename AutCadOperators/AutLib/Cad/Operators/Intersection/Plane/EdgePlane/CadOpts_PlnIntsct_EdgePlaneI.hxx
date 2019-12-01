#pragma once
#include <error.hxx>
#include <OSstream.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Plane.hxx>
#include <CadOpts_PlnIntsct_EdgeEdge.hxx>
namespace AutLib
{

	template<class ObjectSearch>
	void CadOpts_PlnIntsct_EdgePlane<ObjectSearch>::Perform()
	{
		if (NOT Plane())
		{
			FatalErrorIn(" void CadOpts_PlnIntsct_EdgePlane<ObjectSearch>::Perform()")
				<< " no plane has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT Edge())
		{
			FatalErrorIn(" void CadOpts_PlnIntsct_EdgePlane<ObjectSearch>::Perform()")
				<< " no edge has been loaded!" << endl
				<< abort(FatalError);
		}

		auto search = std::make_shared<ObjectSearch>(Plane()->BoundingBox());
		Debug_Null_Pointer(search);

		std::vector<std::shared_ptr<Pln_Edge>> edges;
		Plane()->RetrieveEdgesTo(edges);

		search->Reserve((Standard_Integer)edges.size());
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x);
			search->Insert(x);
		}

		Debug_Null_Pointer(Edge()->Curve());
		auto box = Edge()->Curve()->BoundingBox();
		box = box.OffSet(1.0E-6 * box.Diameter());

		const auto items = search->Search(box);

		if (NOT items.size())
		{
			HasIntersection() = Standard_False;
			Change_IsDone() = Standard_True;

			return;
		}

		Standard_Integer K = 0;
		for (const auto& x : items)
		{
			Debug_Null_Pointer(x);

			auto alg = 
				std::make_shared<CadOpts_PlnIntsct_EdgeEdge>
				(
					Edge(), x,
					Info());

			auto data = alg->Data();
			data->SetIndex(++K);

			if (NOT data->HasIntersection())
			{
				continue;
			}

			theRegister_.insert(std::make_pair(K, data));
		}

		Change_IsDone() = Standard_True;
	}
}