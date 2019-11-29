#pragma once
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class SurfType, class SizeFun, class MetricFun>
	Standard_Boolean Mesh_DefectPatch_OrderWire<SurfType, SizeFun, MetricFun>::Check
	(
		const SurfType & theSurface, 
		std::vector<std::shared_ptr<wireType>>& theWires
	)
	{
		Debug_Null_Pointer(theSurface.OuterWire());
		const auto& Outer = *theSurface.OuterWire();

		if (Check(Outer))
		{
			theWires.push_back(theSurface.OuterWire());
		}

		if (NOT theSurface.InnerWires())
		{
			if (theWires.empty()) return Standard_False;
			else return Standard_True;
		}

		const auto& Inners = *theSurface.InnerWires();
		for (const auto& x : Inners)
		{
			Debug_Null_Pointer(x);
			if (Check(*x))
			{
				theWires.push_back(x);
			}
		}
		if (theWires.empty()) return Standard_False;
		else return Standard_True;
	}

	template<class SurfType, class SizeFun, class MetricFun>
	Standard_Boolean Mesh_DefectPatch_OrderWire<SurfType, SizeFun, MetricFun>::Check
	(
		const wireType & theWire
	)
	{
		if (theWire.NbEdges() IS_EQUAL 1)
		{
			return Standard_False;
		}

		const auto& edges = *theWire.Edges();
		forThose(Index, 1, edges.size() - 1)
		{
			const auto& e0 = edges[Index - 1];
			const auto& e1 = edges[Index];

			const auto& c0 = e0->Par();
			const auto& c1 = e1->Par();

			const auto p0 = c0->Last();

			const auto q0 = c1->Start();
			const auto q1 = c1->Last();

			const auto d0 = Distance(p0, q0);
			const auto d1 = Distance(p0, q1);

			if (d0 >= d1)
			{
				return Standard_True;
			}
		}

		const auto& e0 = edges[edges.size() - 1];
		const auto& e1 = edges[0];

		const auto& c0 = e0->Par();
		const auto& c1 = e1->Par();

		const auto p0 = c0->Last();

		const auto q0 = c1->Start();
		const auto q1 = c1->Last();

		const auto d0 = Distance(p0, q0);
		const auto d1 = Distance(p0, q1);

		if (d0 >= d1)
		{
			return Standard_True;
		}
		return Standard_False;
	}
}