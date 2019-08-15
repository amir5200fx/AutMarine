#include <Istream.hxx>

#include <error.hxx>
#include <OSstream.hxx>
#include <token.hxx>

AutLib::Istream::Istream
(
	streamFormat format, 
	versionNumber version,
	compressionType compression
)
	: IOstream(format, version, compression)
	, putBack_(false)
	, putBackToken_(NULL)
{
	putBackToken_ = new token;
}

AutLib::Istream::~Istream()
{
	delete putBackToken_;
}

// Set t to the put back token if there is one and return true,
// otherwise return false
bool AutLib::Istream::getBack(token& t)
{
	if (bad())
	{
		FatalIOErrorIn("void Istream::getBack(token&)", *this)
			<< "Attempt to get back from bad stream"
			<< exit(FatalIOError);

		return false;
	}
	else if (putBack_)
	{
		t = *putBackToken_;
		putBack_ = false;
		return true;
	}

	return false;
}


// Keep the put back token
void AutLib::Istream::putBack(const token& t)
{
	if (bad())
	{
		FatalIOErrorIn("void Istream::putBack(const token&)", *this)
			<< "Attempt to put back onto bad stream"
			<< exit(FatalIOError);
	}
	else if (putBack_)
	{
		FatalIOErrorIn("void Istream::putBack(const token&)", *this)
			<< "Attempt to put back another token"
			<< exit(FatalIOError);
	}
	else
	{
		*putBackToken_ = t;
		putBack_ = true;
	}
}


// Functions for reading object delimiters ( ... )

AutLib::Istream& AutLib::Istream::readBegin(const char* funcName)
{
	token delimiter(*this);
	if (delimiter != token::BEGIN_LIST)
	{
		setBad();
		FatalIOErrorIn("Istream::readBegin(const char*)", *this)
			<< "Expected a '" << token::BEGIN_LIST
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);
	}

	return *this;
}


AutLib::Istream& AutLib::Istream::readEnd(const char* funcName)
{
	token delimiter(*this);
	if (delimiter != token::END_LIST)
	{
		setBad();
		FatalIOErrorIn("Istream::readEnd(const char*)", *this)
			<< "Expected a '" << token::END_LIST
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);
	}

	return *this;
}


AutLib::Istream& AutLib::Istream::readEndBegin(const char* funcName)
{
	readEnd(funcName);
	return readBegin(funcName);
}


// Functions for reading List delimiters ( ... ) or { ... }

char AutLib::Istream::readBeginList(const char* funcName)
{
	token delimiter(*this);

	if (delimiter != token::BEGIN_LIST && delimiter != token::BEGIN_BLOCK)
	{
		setBad();
		FatalIOErrorIn("Istream::readBeginList(const char*)", *this)
			<< "Expected a '" << token::BEGIN_LIST
			<< "' or a '" << token::BEGIN_BLOCK
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);

		return '\0';
	}

	return delimiter.pToken();
}


char AutLib::Istream::readEndList(const char* funcName)
{
	token delimiter(*this);

	if (delimiter != token::END_LIST && delimiter != token::END_BLOCK)
	{
		setBad();
		FatalIOErrorIn("Istream::readEndList(const char*)", *this)
			<< "Expected a '" << token::END_LIST
			<< "' or a '" << token::END_BLOCK
			<< "' while reading " << funcName
			<< ", found " << delimiter.info()
			<< exit(FatalIOError);

		return '\0';
	}

	return delimiter.pToken();
}


AutLib::Istream& AutLib::Istream::operator()() const
{
	if (!good())
	{
		check("Istream::operator()");
		FatalIOError.exit();
	}

	return const_cast<Istream&>(*this);
}