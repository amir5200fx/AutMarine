#include <dictionaryEntry.hxx>

AutLib::dictionaryEntry::dictionaryEntry
(
	const keyType& key,
	const dictionary& parentDict,
	const dictionary& dict
)
	: entry(key)
	, dictionary(parentDict, dict)
{}


AutLib::dictionaryEntry::dictionaryEntry
(
	const dictionary& parentDict,
	const dictionaryEntry& dictEnt
)
	: entry(dictEnt)
	, dictionary(parentDict, dictEnt)
{}

AutLib::label AutLib::dictionaryEntry::startLineNumber() const
{
	if (size())
	{
		return first()->startLineNumber();
	}
	else
	{
		return -1;
	}
}

AutLib::label AutLib::dictionaryEntry::endLineNumber() const
{
	if (size())
	{
		return last()->endLineNumber();
	}
	else
	{
		return -1;
	}
}


AutLib::ITstream& AutLib::dictionaryEntry::stream() const
{
	FatalIOErrorIn("ITstream& dictionaryEntry::stream() const", *this)
		<< "Attempt to return dictionary entry as a primitive"
		<< abort(FatalIOError);

	return lookup("");
}


const AutLib::dictionary& AutLib::dictionaryEntry::dict() const
{
	return *this;
}


AutLib::dictionary& AutLib::dictionaryEntry::dict()
{
	return *this;
}
