#include <scalarRanges.hxx>

#include <DynamicList.hxx>
#include <ListOps.hxx>

AutLib::scalarRanges::scalarRanges()
	: List<scalarRange>(0)
{
}


AutLib::scalarRanges::scalarRanges(Istream& is)
	: List<scalarRange>(0)
{
	DynamicList<scalarRange> lst;

	while (is.good())
	{
		scalarRange sr(is);
		if (sr.isDefined())
		{
			lst.append(sr);
		}
	}

	transfer(lst);
}

bool AutLib::scalarRanges::selected(const scalar& value) const
{
	for (AutLib::label i = 0; i < (*this).size(); i++)
	{
		if (operator[](i).selected(value))
		{
			return true;
		}
	}

	return false;
}


AutLib::List<bool> AutLib::scalarRanges::selected(const List<scalar>& values) const
{
	List<bool> lst(values.size(), false);

	// check ranges
	for (AutLib::label i = 0; i < (values).size(); i++)
	{
		if (selected(values[i]))
		{
			lst[i] = true;
		}
	}

	// check specific values
	for (AutLib::label rangeI = 0; rangeI < (*this).size(); rangeI++)
	{
		if (operator[](rangeI).isExact())
		{
			scalar target = operator[](rangeI).value();

			int nearestIndex = -1;
			scalar nearestDiff = AutLib::GREAT;

			for (AutLib::label timeIndex = 0; timeIndex < (values).size(); timeIndex++)
			{
				scalar diff = fabs(values[timeIndex] - target);
				if (diff < nearestDiff)
				{
					nearestDiff = diff;
					nearestIndex = timeIndex;
				}
			}

			if (nearestIndex >= 0)
			{
				lst[nearestIndex] = true;
			}
		}
	}

	return lst;
}


AutLib::List<AutLib::scalar> AutLib::scalarRanges::select(const List<scalar>& values) const
{
	return subset(selected(values), values);
}


void AutLib::scalarRanges::inplaceSelect(List<scalar>& values) const
{
	inplaceSubset(selected(values), values);
}