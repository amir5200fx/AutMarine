#include <prefixOSstream.hxx>

#include <token.hxx>

void AutLib::prefixOSstream::checkWritePrefix()
{
	if (printPrefix_ && prefix_.size())
	{
		OSstream::write(prefix_.c_str());
		printPrefix_ = false;
	}
}

AutLib::prefixOSstream::prefixOSstream
(
	ostream& os,
	const string& name,
	streamFormat format,
	versionNumber version,
	compressionType compression
)
	: OSstream(os, name, format, version, compression)
	, printPrefix_(true)
	, prefix_("")
{}

void AutLib::prefixOSstream::print(Ostream& os) const
{
	os << "prefixOSstream ";
	OSstream::print(os);
}


AutLib::Ostream& AutLib::prefixOSstream::write(const token&)
{
	return *this;
}


AutLib::Ostream& AutLib::prefixOSstream::write(const char c)
{
	checkWritePrefix();
	OSstream::write(c);

	if (c == token::NL)
	{
		printPrefix_ = true;
	}

	return *this;
}


AutLib::Ostream& AutLib::prefixOSstream::write(const char* str)
{
	checkWritePrefix();
	OSstream::write(str);

	size_t len = strlen(str);
	if (len && str[len - 1] == token::NL)
	{
		printPrefix_ = true;
	}

	return *this;
}


AutLib::Ostream& AutLib::prefixOSstream::write(const word& val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


AutLib::Ostream& AutLib::prefixOSstream::write(const string& val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


AutLib::Ostream& AutLib::prefixOSstream::writeQuoted
(
	const std::string& val,
	const bool quoted
)
{
	checkWritePrefix();
	return OSstream::writeQuoted(val, quoted);
}


AutLib::Ostream& AutLib::prefixOSstream::write(const label val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


AutLib::Ostream& AutLib::prefixOSstream::write(const floatScalar val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


AutLib::Ostream& AutLib::prefixOSstream::write(const doubleScalar val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


AutLib::Ostream& AutLib::prefixOSstream::write(const longDoubleScalar val)
{
	checkWritePrefix();
	return OSstream::write(val);
}


AutLib::Ostream& AutLib::prefixOSstream::write
(
	const char* buf,
	std::streamsize count
)
{
	checkWritePrefix();
	return OSstream::write(buf, count);
}


void AutLib::prefixOSstream::indent()
{
	checkWritePrefix();
	OSstream::indent();
}