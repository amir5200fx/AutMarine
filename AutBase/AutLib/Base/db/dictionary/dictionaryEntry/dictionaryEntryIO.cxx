#include <dictionaryEntry.hxx>

#include <Istream.hxx>

AutLib::dictionaryEntry::dictionaryEntry
(
	const dictionary& parentDict,
	Istream& is
)
	: entry(keyType(is))
	, dictionary(parentDict, is)
{
	is.fatalCheck
	(
		"dictionaryEntry::dictionaryEntry"
		"(const dictionary& parentDict, Istream&)"
	);
}


AutLib::dictionaryEntry::dictionaryEntry
(
	const keyType& key,
	const dictionary& parentDict,
	Istream& is
)
	: entry(key)
	, dictionary(key, parentDict, is)
{
	is.fatalCheck
	(
		"dictionaryEntry::dictionaryEntry"
		"(const keyType&, const dictionary& parentDict, Istream&)"
	);
}

void AutLib::dictionaryEntry::write(Ostream& os) const
{
	// write keyword with indent but without trailing spaces
	os.indent();
	os.write(keyword());
	dictionary::write(os);
}


namespace AutLib
{
	Ostream& operator<<(Ostream& os, const dictionaryEntry& de)
	{
		de.write(os);
		return os;
	}

	Ostream& operator<<(Ostream& os, const InfoProxy<dictionaryEntry>& ip)
	{
		const dictionaryEntry& e = ip.t_;

		os << "    dictionaryEntry '" << e.keyword() << "'" << endl;

		return os;
	}
}