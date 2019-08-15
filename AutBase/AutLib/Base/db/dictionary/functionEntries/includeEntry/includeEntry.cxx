#include <includeEntry.hxx>

#include <IFstream.hxx>
#include <dictionary.hxx>
#include <primitiveEntry.hxx>

const AutLib::word AutLib::functionEntries::includeEntry::typeName
(
	AutLib::functionEntries::includeEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeEntry
AutLib::debug::debugSwitch
AutLib::functionEntries::includeEntry::debug
(
	"includeEntry",
	0
);

namespace AutLib
{
	namespace functionEntries
	{

		/* Add the includeEntry execute to the table */
		functionEntry::addexecutedictionaryIstreamMemberFunctionToTable<includeEntry>
			addincludeEntryexecutedictionaryIstreamMemberFunctionTofunctionEntryTable_;

		/* Add the includeEntry execute to the table */
		functionEntry::addexecuteprimitiveEntryIstreamMemberFunctionToTable<includeEntry>
			addincludeEntryexecuteprimitiveEntryIstreamMemberFunctionTofunctionEntryTable_;
	}
}

AutLib::fileName AutLib::functionEntries::includeEntry::includeFileName
(
	Istream& is
)
{
	fileName fName(is);
	fName.expand();

	if (fName.size() && fName[0] != '/')
	{
		fName = fileName(is.name()).path() / fName;
	}

	return fName;
}


bool AutLib::functionEntries::includeEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	IFstream fileStream(includeFileName(is));

	if (fileStream)
	{
		parentDict.read(fileStream);
		return true;
	}
	else
	{
		FatalIOErrorIn
		(
			"functionEntries::includeEntry::includeEntry"
			"(dictionary& parentDict,Istream& is)",
			is
		) << "Cannot open include file " << fileStream.name()
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}

bool AutLib::functionEntries::includeEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	IFstream fileStream(includeFileName(is));

	if (fileStream)
	{
		entry.read(parentDict, fileStream);
		return true;
	}
	else
	{
		FatalIOErrorIn
		(
			"functionEntries::includeEntry::includeEntry"
			"(dictionary& parentDict, primitiveEntry& entry, Istream& is)",
			is
		) << "Cannot open include file " << fileStream.name()
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}