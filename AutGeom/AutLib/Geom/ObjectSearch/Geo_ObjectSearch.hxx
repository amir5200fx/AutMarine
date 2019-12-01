#pragma once
#ifndef _Geo_ObjectSearch_Header
#define _Geo_ObjectSearch_Header

#include <Entity_Box.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations

	template<class T>
	class Geo_ObjectSearch
	{

		typedef typename T::ptType Point;

		/*Private Data*/

		Entity_Box<Point> theDomain_;

	protected:

		Geo_ObjectSearch()
		{}

		Geo_ObjectSearch(const Entity_Box<Point>& theDomain)
			: theDomain_(theDomain)
		{}

	public:

		const Entity_Box<Point>& BoundingBox() const
		{
			return theDomain_;
		}

		virtual std::vector<std::shared_ptr<T>> 
			Search(const Entity_Box<Point>& theBox) const = 0;

		void SetDomain(const Entity_Box<Point>& theBox)
		{
			theDomain_ = theBox;
		}
	};
}

#endif // !_Geo_ObjectSearch_Header
