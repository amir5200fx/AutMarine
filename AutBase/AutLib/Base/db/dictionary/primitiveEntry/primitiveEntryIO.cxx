#include <primitiveEntry.hxx>

#include <dictionary.hxx>
#include <IStringStream.hxx>
#include <OSspecific.hxx>
#include <functionEntry.hxx>

#include <ListIO.cxx>

void AutLib::primitiveEntry::append
(
	const token& currToken,
	const dictionary& dict,
	Istream& is
)
{
	if (currToken.isWord())
	{
		const word& w = currToken.wordToken();

		if
			(
				w.size() == 1
				|| (
					!(w[0] == '$' && expandVariable(w, dict))
					&& !(w[0] == '#' && expandFunction(w, dict, is))
					)
				)
		{
			newElmt(tokenIndex()++) = currToken;
		}
	}
	else
	{
		newElmt(tokenIndex()++) = currToken;
	}
}


void AutLib::primitiveEntry::append(const tokenList& varTokens)
{
	for (AutLib::label i = 0; i < (varTokens).size(); i++)
	{
		newElmt(tokenIndex()++) = varTokens[i];
	}
}


bool AutLib::primitiveEntry::expandVariable
(
	const word& w,
	const dictionary& dict
)
{
	word varName = w(1, w.size() - 1);

	// lookup the variable name in the given dictionary....
	// Note: allow wildcards to match? For now disabled since following
	// would expand internalField to wildcard match and not expected
	// internalField:
	//      internalField XXX;
	//      boundaryField { ".*" {YYY;} movingWall {value $internalField;}
	const entry* ePtr = dict.lookupEntryPtr(varName, true, false);

	// ...if defined insert its tokens into this
	if (ePtr != NULL)
	{
		append(ePtr->stream());
		return true;
	}
	else
	{
		// if not in the dictionary see if it is an environment
		// variable

		string enVarString = getEnv(varName);

		if (enVarString.size())
		{
			append(tokenList(IStringStream('(' + enVarString + ')')()));
			return true;
		}

		return false;
	}
}


bool AutLib::primitiveEntry::expandFunction
(
	const word& keyword,
	const dictionary& parentDict,
	Istream& is
)
{
	word functionName = keyword(1, keyword.size() - 1);
	return functionEntry::execute(functionName, parentDict, *this, is);
}


bool AutLib::primitiveEntry::read(const dictionary& dict, Istream& is)
{
	is.fatalCheck
	(
		"primitiveEntry::readData(const dictionary&, Istream&)"
	);

	label blockCount = 0;
	token currToken;

	if
		(
			!is.read(currToken).bad()
			&& currToken.good()
			&& currToken != token::END_STATEMENT
			)
	{
		append(currToken, dict, is);

		if
			(
				currToken == token::BEGIN_BLOCK
				|| currToken == token::BEGIN_LIST
				)
		{
			blockCount++;
		}

		while
			(
				!is.read(currToken).bad()
				&& currToken.good()
				&& !(currToken == token::END_STATEMENT && blockCount == 0)
				)
		{
			if
				(
					currToken == token::BEGIN_BLOCK
					|| currToken == token::BEGIN_LIST
					)
			{
				blockCount++;
			}
			else if
				(
					currToken == token::END_BLOCK
					|| currToken == token::END_LIST
					)
			{
				blockCount--;
			}

			append(currToken, dict, is);
		}
	}

	is.fatalCheck
	(
		"primitiveEntry::readData(const dictionary&, Istream&)"
	);

	if (currToken.good())
	{
		return true;
	}
	else
	{
		return false;
	}
}


void AutLib::primitiveEntry::readEntry(const dictionary& dict, Istream& is)
{
	label keywordLineNumber = is.lineNumber();
	tokenIndex() = 0;

	if (read(dict, is))
	{
		setSize(tokenIndex());
		tokenIndex() = 0;
	}
	else
	{
		// When reading an invalid global controlDict file, the following call
		// to FatalIOErrorIn will crash with a "Segmentation Fault", and will
		// fail to generate any useful error message to the console.
		// This additional error message will at least leave a minimal trace.
		//
		// The cause of the Seg. fault is still unknown, but seems to be related
		// to the initialization of the string member attributes of the global
		// object FatalIOError. (MB 05/2011)
		//
		std::cerr << "--> Error from: "
			<< "primitiveEntry::readEntry(const dictionary&, Istream&)"
			<< std::endl;
		std::cerr << "--> Fatal error reading input from: "
			<< is.name() << std::endl;

		FatalIOErrorIn
		(
			"primitiveEntry::readEntry(const dictionary&, Istream&)",
			is
		) << "ill defined primitiveEntry starting at keyword '"
			<< keyword() << '\''
			<< " on line " << keywordLineNumber
			<< " and ending at line " << is.lineNumber()
			<< exit(FatalIOError);
	}
}


AutLib::primitiveEntry::primitiveEntry
(
	const keyType& key,
	const dictionary& dict,
	Istream& is
)
	:
	entry(key),
	ITstream
	(
		is.name() + "::" + key,
		tokenList(10),
		is.format(),
		is.version()
	)
{
	readEntry(dict, is);
}


AutLib::primitiveEntry::primitiveEntry(const keyType& key, Istream& is)
	: entry(key)
	, ITstream
	(
		is.name() + "::" + key,
		tokenList(10),
		is.format(),
		is.version()
	)
{
	readEntry(dictionary::null, is);
}

void AutLib::primitiveEntry::write(Ostream& os) const
{
	os.writeKeyword(keyword());

	for (label i = 0; i < size(); i++)
	{
		os << operator[](i);

		if (i < size() - 1)
		{
			os << token::SPACE;
		}
	}

	os << token::END_STATEMENT << endl;
}

namespace AutLib
{
	Ostream& operator<<(Ostream& os, const InfoProxy<primitiveEntry>& ip)
	{
		const primitiveEntry& e = ip.t_;

		e.print(os);

		const label nPrintTokens = 10;

		os << "    primitiveEntry '" << e.keyword() << "' comprises ";

		for (label i = 0; i < min(e.size(), nPrintTokens); i++)
		{
			os << nl << "        " << e[i].info();
		}

		if (e.size() > nPrintTokens)
		{
			os << " ...";
		}

		os << endl;

		return os;
	}
}