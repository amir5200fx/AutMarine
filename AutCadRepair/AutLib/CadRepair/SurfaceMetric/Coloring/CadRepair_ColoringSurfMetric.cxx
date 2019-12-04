#include <CadRepair_ColoringSurfMetric.hxx>

#include <Adt_AvlTree.hxx>
#include <Entity2d_Metric1.hxx>
#include <Mesh2d_Element.hxx>
#include <Mesh2d_Node.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <CadRepair_ApproxSurfMetric.hxx>
#include <CadRepair_ApproxSurfMetric_Info.hxx>
#include <GeoMesh2d_MetricBackground.hxx>

#include <Geom_Surface.hxx>

namespace AutLib
{

	typedef CadRepair_ColoringSurfMetric::elementColor elementColor;
	typedef std::vector<std::shared_ptr<Mesh2d_Element>> elementList;
	typedef Entity2d_Metric1 metric;

	template<class SizeMap = void>
	struct MetricAt
	{
		static metric _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const Pnt2d& theP
		)
		{
			auto u = theP.X();
			auto v = theP.Y();

			gp_Vec D1U, D1V;
			gp_Pnt P;
			theSurface.D1(u, v, P, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			const auto h = theMap.Value(theP);
			Debug_If_Condition(h <= gp::Resolution());

			const auto invH = 1.0 / (h * h);

			metric M(invH * A, invH * B, invH * C);
			return std::move(M);
		}
	};

	template<>
	struct MetricAt<void>
	{
		static metric _
		(
			const Geom_Surface& theSurface,
			const Pnt2d& theP
		)
		{
			auto u = theP.X();
			auto v = theP.Y();

			gp_Vec D1U, D1V;
			gp_Pnt P;
			theSurface.D1(u, v, P, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			metric M(A, B, C);
			return std::move(M);
		}
	};

	template<class SizeMap = void>
	struct IsDegenerated
	{

		static inline Standard_Boolean _
		(
			const Mesh2d_Element& theElement,
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet
		)
		{
			const auto& P0 = theElement.Node0()->Coord();
			const auto& P1 = theElement.Node1()->Coord();
			const auto& P2 = theElement.Node2()->Coord();

			auto m0 = MetricAt<SizeMap>::_(theSurface, theMap, P0);
			if (m0.Determinant() * theInvMaxDet <= theDegeneracy) return Standard_True;

			auto m1 = MetricAt<SizeMap>::_(theSurface, theMap, P1);
			if (m1.Determinant() * theInvMaxDet <= theDegeneracy) return Standard_True;

			auto m2 = MetricAt<SizeMap>::_(theSurface, theMap, P2);
			if (m2.Determinant() * theInvMaxDet <= theDegeneracy) return Standard_True;

			return Standard_False;
		}
	};

	template<>
	struct IsDegenerated<void>
	{

		static inline Standard_Boolean _
		(
			const Mesh2d_Element& theElement,
			const Geom_Surface& theSurface,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet
		)
		{
			const auto& P0 = theElement.Node0()->Coord();
			const auto& P1 = theElement.Node1()->Coord();
			const auto& P2 = theElement.Node2()->Coord();

			auto m0 = MetricAt<>::_(theSurface, P0);
			if (m0.Determinant() * theInvMaxDet <= theDegeneracy) return Standard_True;

			auto m1 = MetricAt<>::_(theSurface, P1);
			if (m1.Determinant() * theInvMaxDet <= theDegeneracy) return Standard_True;

			auto m2 = MetricAt<>::_(theSurface, P2);
			if (m2.Determinant() * theInvMaxDet <= theDegeneracy) return Standard_True;

			return Standard_False;
		}
	};

	template<class SizeMap = void>
	struct RegisterElementsOnSingularities
	{

		static void _
		(
			const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements,
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theRegister
		)
		{
			for (const auto& x : theElements)
			{
				Debug_Null_Pointer(x);
				const auto& element = *x;

				if (IsDegenerated<SizeMap>::_(element, theSurface, theMap, theDegeneracy, theInvMaxDet))
				{
					theRegister.Insert(x);
				}
			}
		}
	};

	template<>
	struct RegisterElementsOnSingularities<void>
	{

		static void _
		(
			const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements,
			const Geom_Surface& theSurface,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theRegister
		)
		{
			for (const auto& x : theElements)
			{
				Debug_Null_Pointer(x);
				const auto& element = *x;

				if (IsDegenerated<>::_(element, theSurface, theDegeneracy, theInvMaxDet))
				{
					theRegister.Insert(x);
				}
			}
		}
	};

	static void TrackRegion
	(
		const Mesh2d_Element& theElement,
		Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theElements,
		elementList& theList
	)
	{
		const auto n0 = theElement.Neighbor0().lock();
		if (n0 AND NOT theElements.RemoveIgnoreWarning(n0))
		{
			theList.push_back(n0);
			TrackRegion(*n0, theElements, theList);
		}

		const auto n1 = theElement.Neighbor1().lock();
		if (n1 AND NOT theElements.RemoveIgnoreWarning(n1))
		{
			theList.push_back(n1);
			TrackRegion(*n1, theElements, theList);
		}

		const auto n2 = theElement.Neighbor2().lock();
		if (n2 AND NOT theElements.RemoveIgnoreWarning(n2))
		{
			theList.push_back(n2);
			TrackRegion(*n2, theElements, theList);
		}
	}

	static std::vector<std::shared_ptr<elementList>>
		TrackRegions
		(
			Adt_AvlTree<std::shared_ptr<Mesh2d_Element>>& theDegtElements
		)
	{
		std::vector<std::shared_ptr<elementList>> regions;
		while (theDegtElements.Size())
		{
			auto l = std::make_shared<elementList>();

			std::shared_ptr<Mesh2d_Element> root;
			theDegtElements.Root(root);
			theDegtElements.Remove(root);

			l->push_back(root);

			TrackRegion(*root, theDegtElements, *l);

			regions.push_back(l);
		}
		return std::move(regions);
	}

	static std::vector<elementColor> MarkElements
	(
		const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements,
		const Geom_Surface& theSurface,
		const std::shared_ptr<Geo2d_SizeFunction>& theMap,
		const Standard_Real theDegeneracy,
		const Standard_Real theInvMaxDet,
		Standard_Integer& theMaxNb
	)
	{
		Adt_AvlTree<std::shared_ptr<Mesh2d_Element>> Register;
		Register.SetComparableFunction(&Mesh2d_Element::IsLess);

		if (theMap)
		{
			RegisterElementsOnSingularities<Geo2d_SizeFunction>::_
			(
				theElements,
				theSurface,
				*theMap,
				theDegeneracy,
				theInvMaxDet,
				Register
			);
		}
		else
		{
			RegisterElementsOnSingularities<>::_
			(
				theElements,
				theSurface,
				theDegeneracy,
				theInvMaxDet,
				Register
			);
		}


		std::vector<elementColor> marks(theElements.size());
		for (const auto& x : theElements)
		{
			marks[Index_Of(x->Index())] = std::make_pair(x, 0);
		}

		auto regions = TrackRegions(Register);

		if (Register.Size())
		{
			FatalErrorIn("void MarkElements()")
				<< "the tree is not empty" << endl
				<< abort(FatalError);
		}

		Standard_Integer K = 0;
		for (const auto& reg : regions)
		{
			Debug_Null_Pointer(reg);
			const auto& region = *reg;

			++K;

			for (const auto& x : region)
			{
				marks[Index_Of(x->Index())].second = K;
			}
		}
		theMaxNb = K;

		return std::move(marks);
	}
}

Standard_Integer
AutLib::CadRepair_ColoringSurfMetric::Value
(
	const Pnt2d& theCoord
) const
{
	if (NOT theApprox_)
	{
		FatalErrorIn("void AutLib::Geo_ColoringSurfMetric::Perform()")
			<< "Found no surface metric approximation" << endl
			<< abort(FatalError);
	}

	if (NOT theApprox_->Approx())
	{
		FatalErrorIn("void AutLib::Geo_ColoringSurfMetric::Perform()")
			<< "Found no surface metric approximation" << endl
			<< abort(FatalError);
	}

	const auto& apprx = *theApprox_->Approx();

	Debug_Null_Pointer(apprx.Mesh());
	const auto& mesh = *apprx.Mesh();

	const auto& element = mesh.TriangleLocation(mesh.FirstElement(), theCoord);

	return Value(Index_Of(element->Index()));
}

void AutLib::CadRepair_ColoringSurfMetric::Perform()
{
	if (NOT theApprox_)
	{
		FatalErrorIn("void AutLib::Geo_ColoringSurfMetric::Perform()")
			<< "Found no surface metric approximation" << endl
			<< abort(FatalError);
	}

	if (NOT theApprox_->Approx())
	{
		FatalErrorIn("void AutLib::Geo_ColoringSurfMetric::Perform()")
			<< "Found no surface metric approximation" << endl
			<< abort(FatalError);
	}

	const auto& apprx = *theApprox_->Approx();

	Debug_Null_Pointer(theApprox_->Surface());
	const auto& surface = *theApprox_->Surface();

	Debug_Null_Pointer(apprx.Mesh());
	const auto& mesh = *apprx.Mesh();

	const auto& info = *theApprox_->Info();
	const auto invMaxDet =
		(Standard_Real)1.0 / theApprox_->MaxDet();

	const auto& elements = mesh.Elements();

	Standard_Integer nbRegions;
	theElements_ =
		MarkElements
		(
			elements,
			surface,
			theApprox_->SizeFunction(),
			info.Degeneracy(), invMaxDet, nbRegions);

	Change_IsDone() = Standard_True;
}