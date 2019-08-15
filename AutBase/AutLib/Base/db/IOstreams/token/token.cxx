#include <token.hxx>

#include <wordList.hxx>
#include <HashTable.hxx>

const char* const AutLib::token::typeName = "token";
AutLib::token AutLib::token::undefinedToken;

const ::AutLib::word AutLib::token::compound::typeName(AutLib::token::compound::typeName_());
::AutLib::debug::debugSwitch AutLib::token::compound::debug(std::string(AutLib::token::compound::typeName_()), 0, "");

/* Define the constructor function table */
AutLib::token::compound::IstreamConstructorTable*
AutLib::token::compound::IstreamConstructorTablePtr_ = NULL;

void AutLib::token::compound::constructIstreamConstructorTables()
{
	static bool constructed = false;

	if (!constructed)
	{
		AutLib::token::compound::IstreamConstructorTablePtr_
			= new AutLib::token::compound::IstreamConstructorTable;

		constructed = true;
	}
}

void AutLib::token::compound::destroyIstreamConstructorTables()
{
	if (AutLib::token::compound::IstreamConstructorTablePtr_)
	{
		delete AutLib::token::compound::IstreamConstructorTablePtr_;
		AutLib::token::compound::IstreamConstructorTablePtr_ = NULL;
	}
}

void AutLib::token::parseError(const char* expected) const
{
	FatalIOError
		<< "Parse error, expected a " << expected
		<< ", found \n    " << info() << endl;
}

AutLib::token::compound::~compound()
{
}

AutLib::autoPtr<AutLib::token::compound> AutLib::token::compound::New
(
	const word& compoundType,
	Istream& is
)
{
	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(compoundType);
	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		FatalErrorIn("token::compound::New(const word&, Istream&)")
			<< "Unknown compound type " << compoundType << nl << nl
			<< "Valid compound types:" << endl
			<< IstreamConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<AutLib::token::compound>(cstrIter()(is));
}

bool AutLib::token::compound::isCompound(const word& name)
{
	return
		(
			IstreamConstructorTablePtr_
			&& IstreamConstructorTablePtr_->found(name)
			);
}

AutLib::token::compound& AutLib::token::transferCompoundToken()
{
	if (type_ == COMPOUND)
	{
		if (compoundTokenPtr_->empty())
		{
			FatalErrorIn("token::transferCompoundToken()")
				<< "compound has already been transfered from token\n    "
				<< info() << abort(FatalError);
		}
		else
		{
			compoundTokenPtr_->empty() = true;
		}

		return *compoundTokenPtr_;
	}
	else
	{
		parseError("compound");
		return *compoundTokenPtr_;
	}
}