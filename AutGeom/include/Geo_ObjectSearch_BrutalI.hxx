#pragma once
namespace AutLib
{

	template<class T>
	std::vector<std::shared_ptr<T>> Geo_ObjectSearch_Brutal<T>::Search
	(
		const Entity_Box<Point>& theBox
	) const
	{
		std::vector<std::shared_ptr<T>> Items;
		for (const auto& x : theObjects_)
		{
			if (theBox.IsIntersect(x->BoundingBox()))
			{
				Items.push_back(x);
			}
		}
		return std::move(Items);
	}
}