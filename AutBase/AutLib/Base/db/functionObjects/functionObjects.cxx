#include <functionObjects.hxx>

#include <dictionary.hxx>
#include <dlLibraryTable.hxx>

/* Define the constructor function table */
AutLib::functionObject::dictionaryConstructorTable*
AutLib::functionObject::dictionaryConstructorTablePtr_ = NULL;

/* Table constructor called from the table add function */
void AutLib::functionObject::constructdictionaryConstructorTables()
{
	static bool constructed = false;

	if (!constructed)
	{
		AutLib::functionObject::dictionaryConstructorTablePtr_
			= new AutLib::functionObject::dictionaryConstructorTable;

		constructed = true;
	}
}

/* Table destructor called from the table add function destructor */
void AutLib::functionObject::destroydictionaryConstructorTables()
{
	if (AutLib::functionObject::dictionaryConstructorTablePtr_)
	{
		delete AutLib::functionObject::dictionaryConstructorTablePtr_;
		AutLib::functionObject::dictionaryConstructorTablePtr_ = NULL;
	}
}

//defineRunTimeSelectionTable(AutLib::functionObject, dictionary);

AutLib::debug::debugSwitch
AutLib::functionObject::debug
(
	"functionObject",
	0
);

AutLib::functionObject::functionObject(const word& name)
	: name_(name)
{}

AutLib::autoPtr<AutLib::functionObject> AutLib::functionObject::New
(
	const word& name,
	const Time& t,
	const dictionary& functionDict
)
{
	word functionType(functionDict.lookup("type"));

	if (debug)
	{
		Info << "Selecting function " << functionType << endl;
	}

	dlLibraryTable::open
	(
		functionDict,
		"functionObjectLibs",
		dictionaryConstructorTablePtr_
	);

	if (!dictionaryConstructorTablePtr_)
	{
		FatalErrorIn
		(
			"functionObject::New"
			"(const word& name, const Time&, const dictionary&)"
		) << "Unknown function type "
			<< functionType << nl << nl
			<< "Table of functionObjects is empty" << endl
			<< exit(FatalError);
	}

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(functionType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"functionObject::New"
			"(const word& name, const Time&, const dictionary&)"
		) << "Unknown function type "
			<< functionType << nl << nl
			<< "Valid functions are : " << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << endl
			<< exit(FatalError);
	}

	return autoPtr<functionObject>(cstrIter()(name, t, functionDict));
}

AutLib::functionObject::~functionObject()
{}

const AutLib::word& AutLib::functionObject::name() const
{
	return name_;
}


bool AutLib::functionObject::end()
{
	return execute();
}


AutLib::autoPtr<AutLib::functionObject> AutLib::functionObject::iNew::operator()
(
	const word& name,
	Istream& is
	) const
{
	dictionary dict(is);
	return functionObject::New(name, time_, dict);
}