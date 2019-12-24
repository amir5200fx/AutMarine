#pragma once
#ifndef _Geo_BinSearch_Header
#define _Geo_BinSearch_Header

#include <Geo_ItemSearch.hxx>
#include <Adt_AvlTree.hxx>
#include <Traits.hxx>

#include <array>

namespace AutLib
{

	template<class T>
	class Geo_BinSearch
	{

		typedef typename T::ptType Point;

		/*Private Data*/

		std::array<Standard_Integer, (size_t)Point::dim>
			theNbSections_;

		std::array<Standard_Real, (size_t)Point::dim>
			theD_;

		Entity_Box<Point> theDomain_;

		std::vector
			<
			std::shared_ptr
			<
			std::map
			<
			Standard_Integer,
			std::shared_ptr<T>
			>>> theTable_;


		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		Standard_Integer KeyX(const Standard_Real theX) const;

		Standard_Integer KeyY(const Standard_Real theX) const;

		template<class U = Standard_Integer>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			> 
			KeyZ(const Standard_Real theX) const
		{
			return (Standard_Integer)((theX - Pmin().Z()) / std::get<2>(D)) + 1;
		}

		const std::vector
			<
			std::shared_ptr
			<
			std::map
			<
			Standard_Integer,
			std::shared_ptr<T>
			>>>& Table() const
		{
			return theTable_;
		}

	public:

		Geo_BinSearch(const Entity_Box<Point>& theDomain)
			: theDomain_(theDomain)
		{}

		const Point& Pmin() const
		{
			return theDomain_.P0();
		}

		const std::array<Standard_Integer, (size_t)Point::dim>& NbSections() const
		{
			return theNbSections_;
		}

		std::array<Standard_Integer, (size_t)Point::dim>& NbSections()
		{
			return theNbSections_;
		}

		const std::array<Standard_Real, (size_t)Point::dim>& D() const
		{
			return theD_;
		}

		template<class U = std::vector<std::shared_ptr<T>>>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			Search(const Entity_Box<Point>& theBox) const
		{
			const auto& pmin = theBox.P0();
			const auto& pmax = theBox.P1();

			const auto i0 = KeyX(pmin.X());
			const auto i1 = KeyX(pmax.X());

			const auto j0 = KeyY(pmin.Y());
			const auto j1 = KeyY(pmin.Y());

			const auto nx = std::get<0>(NbSections());
			const auto ny = std::get<1>(NbSections());

			const auto& table = Table();
			const auto nt = table.size();

			Adt_AvlTree<T> tree;
			tree.SetComparableFunction(&T::IsLess);

			for (auto j = j0; j <= j1; j++)
			{
				for (auto i = i0; i <= i1; i++)
				{
					auto l = (j - 1) * nx + i;

					Debug_If_Condition_Message(NOT INSIDE(l, 0, nt), "Exceed array size");

					if (table[l])
					{
						for (const auto& x : *table[l])
						{
							tree.InsertIgnoreDup(x);
						}
					}
				}
			}

			std::vector<std::shared_ptr<T>> items;
			tree.RetrieveTo(items);

			return std::move(items);
		}


		template<class U = std::vector<std::shared_ptr<T>>>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			Search(const Entity_Box<Point>& theBox) const
		{
			const auto& pmin = theBox.P0();
			const auto& pmax = theBox.P1();

			const auto i0 = KeyX(pmin.X());
			const auto i1 = KeyX(pmax.X());

			const auto j0 = KeyY(pmin.Y());
			const auto j1 = KeyY(pmin.Y());

			const auto k0 = KeyZ(pmin.Z());
			const auto k1 = KeyZ(pmax.Z());

			const auto nx = std::get<0>(NbSections());
			const auto ny = std::get<1>(NbSections());
			const auto nz = std::get<2>(NbSections());

			const auto& table = Table();
			const auto nt = table.size();

			Adt_AvlTree<T> tree;
			tree.SetComparableFunction(&T::IsLess);

			for (auto k = k0; k <= k1; k++)
			{
				for (auto j = j0; j <= j1; j++)
				{
					for (auto i = i0; i <= i1; i++)
					{
						auto l = (k - 1) * nx * ny + (j - 1) * nx + i;

						Debug_If_Condition_Message(NOT INSIDE(l, 0, nt), "Exceed array size");

						if (table[l])
						{
							for (const auto& x : *table[l])
							{
								tree.InsertIgnoreDup(x);
							}
						}
					}
				}
			}

			std::vector<std::shared_ptr<T>> items;
			tree.RetrieveTo(items);

			return std::move(items);
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			Register(const std::vector<std::shared_ptr<T>>& theItems)
		{

		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			Register(const std::vector<std::shared_ptr<T>>& theItems)
		{
			for (const auto& x : theItems)
			{
				const auto& b = x->BoundingBox();

				auto pmin = b.P0();
				auto pmax = b.P1();


			}
		}
	};
}

#include <Geo_BinSearchI.hxx>

#endif // !_Geo_BinSearch_Header
