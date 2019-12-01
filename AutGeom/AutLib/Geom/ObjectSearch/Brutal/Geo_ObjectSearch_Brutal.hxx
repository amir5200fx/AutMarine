#pragma once
#ifndef _Geo_ObjectSearch_Brutal_Header
#define _Geo_ObjectSearch_Brutal_Header

#include <Geo_ObjectSearch.hxx>

#include <list>

namespace AutLib
{

	template<class T>
	class Geo_ObjectSearch_Brutal
		: public Geo_ObjectSearch<T>
	{

		/*Private Data*/

		std::list<std::shared_ptr<T>> theObjects_;

	public:

		typedef Geo_ObjectSearch<T> base;
		typedef typename base::Point Point;

		Geo_ObjectSearch_Brutal()
		{}

		Geo_ObjectSearch_Brutal
		(
			const Entity_Box<Point>& theBox
		)
			: base(theBox)
		{}

		const std::list<std::shared_ptr<T>>& Items() const
		{
			return theObjects_;
		}

		std::vector<std::shared_ptr<T>> 
			Search(const Entity_Box<Point>& theBox) const override;

		void Insert(const std::shared_ptr<T>& theItem)
		{
			theObjects_.push_back(theItem);
		}

		void Reserve(const Standard_Integer theSize)
		{
			theObjects_.reserve(theSize);
		}

		void Remove(const std::shared_ptr<T>& theItem)
		{
			theObjects_.remove(theItem);
		}
	};
}

#include <Geo_ObjectSearch_BrutalI.hxx>

#endif // !_Geo_ObjectSearch_Brutal_Header
