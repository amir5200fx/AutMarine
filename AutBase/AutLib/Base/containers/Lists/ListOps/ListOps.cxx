#include <ListOps.hxx>

AutLib::labelList AutLib::invert
(
	const label len,
	const UList<label>& map
)
{
	labelList inverse(len, -1);

	for (label i = 0; i < (map).size(); i++)
	{
		label newPos = map[i];

		if (newPos >= 0)
		{
			if (inverse[newPos] >= 0)
			{
				FatalErrorIn("invert(const label, const UList<label>&)")
					<< "Map is not one-to-one. At index " << i
					<< " element " << newPos << " has already occurred before"
					<< nl << "Please use invertOneToMany instead"
					<< abort(FatalError);
			}

			inverse[newPos] = i;
		}
	}
	return inverse;
}


AutLib::labelListList AutLib::invertOneToMany
(
	const label len,
	const UList<label>& map
)
{
	labelList nElems(len, 0);

	for (label i = 0; i < (map).size(); i++)
	{
		if (map[i] >= 0)
		{
			nElems[map[i]]++;
		}
	}

	labelListList inverse(len);

	for (label i = 0; i < (nElems).size(); i++)
	{
		inverse[i].setSize(nElems[i]);
		nElems[i] = 0;
	}

	for (label i = 0; i < (map).size(); i++)
	{
		label newI = map[i];

		if (newI >= 0)
		{
			inverse[newI][nElems[newI]++] = i;
		}
	}

	return inverse;
}


AutLib::labelList AutLib::identity(const label len)
{
	labelList map(len);

	for (label i = 0; i < (map).size(); i++)
	{
		map[i] = i;
	}
	return map;
}