#include <IOstream.hxx>

#include <Switch.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <sstream>

AutLib::fileName AutLib::IOstream::name_("IOstream");

AutLib::IOstream::streamFormat
AutLib::IOstream::formatEnum(const word& format)
{
	if (format == "ascii")
	{
		return IOstream::ASCII;
	}
	else if (format == "binary")
	{
		return IOstream::BINARY;
	}
	else
	{
		WarningIn("IOstream::formatEnum(const word&)")
			<< "bad format specifier '" << format << "', using 'ascii'"
			<< endl;

		return IOstream::ASCII;
	}
}


AutLib::IOstream::compressionType
AutLib::IOstream::compressionEnum(const word& compression)
{
	// get Switch (bool) value, but allow it to fail
	Switch sw(compression, true);

	if (sw.valid())
	{
		return sw ? IOstream::COMPRESSED : IOstream::UNCOMPRESSED;
	}
	else if (compression == "uncompressed")
	{
		return IOstream::UNCOMPRESSED;
	}
	else if (compression == "compressed")
	{
		return IOstream::COMPRESSED;
	}
	else
	{
		WarningIn("IOstream::compressionEnum(const word&)")
			<< "bad compression specifier '" << compression
			<< "', using 'uncompressed'"
			<< endl;

		return IOstream::UNCOMPRESSED;
	}
}

bool AutLib::IOstream::check(const char* operation) const
{
	if (bad())
	{
		FatalIOErrorIn("IOstream::check(const char*) const", *this) 
			<< "error in IOstream " 
			<< name() 
			<< " for operation " 
			<< operation
			<< exit(FatalIOError);
	}

	return !bad();
}


void AutLib::IOstream::fatalCheck(const char* operation) const
{
	if (bad())
	{
		FatalIOErrorIn("IOstream::fatalCheck(const char*) const", *this) 
			<< "error in IOstream " 
			<< name() 
			<< " for operation " 
			<< operation
			<< exit(FatalIOError);
	}
}


AutLib::string AutLib::IOstream::versionNumber::str() const
{
	std::ostringstream os;
	os.precision(1);
	os.setf(ios_base::fixed, ios_base::floatfield);
	os << versionNumber_;
	return os.str();
}


void AutLib::IOstream::print(Ostream& os) const
{
	os << "IOstream: " << "Version " << version_ << ", format ";

	switch (format_)
	{
	case ASCII:
		os << "ASCII";
		break;

	case BINARY:
		os << "BINARY";
		break;
	}

	os << ", line " << lineNumber();

	if (opened())
	{
		os << ", OPENED";
	}

	if (closed())
	{
		os << ", CLOSED";
	}

	if (good())
	{
		os << ", GOOD";
	}

	if (eof())
	{
		os << ", EOF";
	}

	if (fail())
	{
		os << ", FAIL";
	}

	if (bad())
	{
		os << ", BAD";
	}

	os << endl;
}


void AutLib::IOstream::print(Ostream& os, const int streamState) const
{
	if (streamState == ios_base::goodbit)
	{
		os << "ios_base::goodbit set : the last operation on stream succeeded"
			<< endl;
	}
	else if (streamState & ios_base::badbit)
	{
		os << "ios_base::badbit set : characters possibly lost"
			<< endl;
	}
	else if (streamState & ios_base::failbit)
	{
		os << "ios_base::failbit set : some type of formatting error"
			<< endl;
	}
	else if (streamState & ios_base::eofbit)
	{
		os << "ios_base::eofbit set : at end of stream"
			<< endl;
	}
}

namespace AutLib
{
	Ostream& operator<<(Ostream& os, const IOstream::streamFormat& sf)
	{
		if (sf == IOstream::ASCII)
		{
			os << "ascii";
		}
		else
		{
			os << "binary";
		}

		return os;
	}


	Ostream& operator<<(Ostream& os, const IOstream::versionNumber& vn)
	{
		os << vn.str().c_str();
		return os;
	}

	Ostream& operator<<(Ostream& os, const InfoProxy<IOstream>& ip)
	{
		ip.t_.print(os);
		return os;
	}
}

