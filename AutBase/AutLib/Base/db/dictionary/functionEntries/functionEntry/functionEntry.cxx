#include <functionEntry.hxx>

#include <Istream.hxx>
#include <List.hxx>

namespace AutLib
{
	/* Define the execute table */
	functionEntry::executedictionaryIstreamMemberFunctionTable*
		functionEntry::executedictionaryIstreamMemberFunctionTablePtr_ = NULL;

	/* Table execute called from the table add function */
	void functionEntry::constructexecutedictionaryIstreamMemberFunctionTables()
	{
		static bool constructed = false;

		if (!constructed)
		{
			functionEntry::executedictionaryIstreamMemberFunctionTablePtr_
				= new functionEntry::executedictionaryIstreamMemberFunctionTable;

			constructed = true;
		}
	}

	/* Table destructor called from the table add function destructor */
	void functionEntry::destroyexecutedictionaryIstreamMemberFunctionTables()
	{
		if (functionEntry::executedictionaryIstreamMemberFunctionTablePtr_)
		{
			delete functionEntry::executedictionaryIstreamMemberFunctionTablePtr_;
			functionEntry::executedictionaryIstreamMemberFunctionTablePtr_ = NULL;
		}
	}

	/* Define the execute table */
	functionEntry::executeprimitiveEntryIstreamMemberFunctionTable*
		functionEntry::executeprimitiveEntryIstreamMemberFunctionTablePtr_ = NULL;

	/* Table execute called from the table add function */
	void functionEntry::constructexecuteprimitiveEntryIstreamMemberFunctionTables()
	{
		static bool constructed = false;

		if (!constructed)
		{
			functionEntry::executeprimitiveEntryIstreamMemberFunctionTablePtr_
				= new functionEntry::executeprimitiveEntryIstreamMemberFunctionTable;

			constructed = true;
		}
	}

	/* Table destructor called from the table add function destructor */
	void functionEntry::destroyexecuteprimitiveEntryIstreamMemberFunctionTables()
	{
		if (functionEntry::executeprimitiveEntryIstreamMemberFunctionTablePtr_)
		{
			delete functionEntry::executeprimitiveEntryIstreamMemberFunctionTablePtr_;
			functionEntry::executeprimitiveEntryIstreamMemberFunctionTablePtr_ = NULL;
		}
	}
}

bool AutLib::functionEntry::execute
(
	const word& functionName,
	dictionary& parentDict,
	Istream& is
)
{
	is.fatalCheck
	(
		"functionEntry::execute"
		"(const word& functionName, dictionary& parentDict, Istream&)"
	);

	if (!executedictionaryIstreamMemberFunctionTablePtr_)
	{
		cerr << "functionEntry::execute"
			<< "(const word&, dictionary&, Istream&)"
			<< " not yet initialized, function = "
			<< functionName.c_str() << std::endl;

		// Return true to keep reading
		return true;
	}

	executedictionaryIstreamMemberFunctionTable::iterator mfIter =
		executedictionaryIstreamMemberFunctionTablePtr_->find(functionName);

	if (mfIter == executedictionaryIstreamMemberFunctionTablePtr_->end())
	{
		FatalErrorIn
		(
			"functionEntry::execute"
			"(const word& functionName, dictionary& parentDict, Istream&)"
		) << "Unknown functionEntry '" << functionName
			<< "' in " << is.name() << " near line " << is.lineNumber()
			<< endl << endl
			<< "Valid functionEntries are :" << endl
			<< executedictionaryIstreamMemberFunctionTablePtr_->toc()
			<< exit(FatalError);
	}

	return mfIter()(parentDict, is);
}


bool AutLib::functionEntry::execute
(
	const word& functionName,
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	is.fatalCheck
	(
		"functionEntry::execute"
		"(const word&, const dictionary&, primitiveEntry&, Istream&)"
	);

	if (!executeprimitiveEntryIstreamMemberFunctionTablePtr_)
	{
		cerr << "functionEntry::execute"
			<< "(const word&, const dictionary&, primitiveEntry&, Istream&)"
			<< " not yet initialized, function = "
			<< functionName.c_str() << std::endl;

		// return true to keep reading anyhow
		return true;
	}

	executeprimitiveEntryIstreamMemberFunctionTable::iterator mfIter =
		executeprimitiveEntryIstreamMemberFunctionTablePtr_->find(functionName);

	if (mfIter == executeprimitiveEntryIstreamMemberFunctionTablePtr_->end())
	{
		FatalErrorIn
		(
			"functionEntry::execute"
			"(const word&, const dictionary&, primitiveEntry&, Istream&)"
		) << "Unknown functionEntry '" << functionName
			<< "' in " << is.name() << " near line " << is.lineNumber()
			<< endl << endl
			<< "Valid functionEntries are :" << endl
			<< executeprimitiveEntryIstreamMemberFunctionTablePtr_->toc()
			<< exit(FatalError);
	}

	return mfIter()(parentDict, entry, is);
}