#include <HashTable.hxx>

#include <uLabel.hxx>

namespace AutLib
{
	const ::AutLib::word HashTableCore::typeName(HashTableCore::typeName_());
	::AutLib::debug::debugSwitch HashTableCore::debug(std::string(HashTableCore::typeName_()), 0, "");;
}

const AutLib::label AutLib::HashTableCore::maxTableSize
(
	AutLib::HashTableCore::canonicalSize
	(
		AutLib::labelMax / 2
	)
);

AutLib::label AutLib::HashTableCore::canonicalSize(const label size)
{
	if (size < 1)
	{
		return 0;
	}

	// enforce power of two
	uLabel goodSize = size;

	if (goodSize & (goodSize - 1))
	{
		// brute-force is fast enough
		goodSize = 1;
		while (goodSize < unsigned(size))
		{
			goodSize <<= 1;
		}
	}

	return goodSize;
}