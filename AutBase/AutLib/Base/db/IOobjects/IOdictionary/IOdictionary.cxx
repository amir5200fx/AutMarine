#include <IOdictionary.hxx>

const ::AutLib::word AutLib::IOdictionary::typeName(AutLib::IOdictionary::typeName_());
::AutLib::debug::debugSwitch AutLib::IOdictionary::debug(std::string(AutLib::IOdictionary::typeName_()), 0, "");

AutLib::IOdictionary::IOdictionary(const IOobject& io)
	: regIOobject(io)
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}

	dictionary::name() = IOobject::objectPath();
}


AutLib::IOdictionary::IOdictionary(const IOobject& io, const dictionary& dict)
	: regIOobject(io)
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
	else
	{
		dictionary::operator=(dict);
	}

	dictionary::name() = IOobject::objectPath();
}

AutLib::IOdictionary::~IOdictionary()
{}

const AutLib::word& AutLib::IOdictionary::name() const
{
	return regIOobject::name();
}

void AutLib::IOdictionary::operator=(const IOdictionary& rhs)
{
	dictionary::operator=(rhs);
}