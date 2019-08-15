#include <OPstream.hxx>
#include <token.hxx>

void AutLib::OPstream::writeToBuffer(const char& c)
{
	if (size_t(buf_.size()) < bufPosition_ + 1U)
	{
		enlargeBuffer(1);
	}

	buf_[bufPosition_] = c;
	bufPosition_++;
}


void AutLib::OPstream::writeToBuffer
(
	const void* data,
	size_t count,
	size_t align
)
{
	label oldPos = bufPosition_;

	if (align > 1)
	{
		// Align bufPosition. Pads bufPosition_ - oldPos characters.
		bufPosition_ = (int)align + ((bufPosition_ - 1) & ~((int)align - 1));
	}

	if (size_t(buf_.size()) < bufPosition_ + count)
	{
		enlargeBuffer(bufPosition_ - oldPos + count);
	}

	register char* bufPtr = &buf_[bufPosition_];
	register const char* dataPtr = reinterpret_cast<const char*>(data);
	register size_t i = count;
	while (i--) *bufPtr++ = *dataPtr++;

	bufPosition_ += (int)count;
}

AutLib::OPstream::OPstream
(
	const commsTypes commsType,
	const int toProcNo,
	const label bufSize,
	streamFormat format,
	versionNumber version
)
	: Pstream(commsType, bufSize)
	, Ostream(format, version)
	, toProcNo_(toProcNo)
{
	setOpened();
	setGood();

	if (!bufSize)
	{
		buf_.setSize(1000);
	}
}

AutLib::Ostream& AutLib::OPstream::write(const token&)
{
	notImplemented("Ostream& OPstream::write(const token&)");
	setBad();
	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const char c)
{
	if (!isspace(c))
	{
		writeToBuffer(c);
	}

	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const char* str)
{
	word nonWhiteChars(string::validate<word>(str));

	if (nonWhiteChars.size() == 1)
	{
		return write(nonWhiteChars.c_str()[1]);
	}
	else if (nonWhiteChars.size())
	{
		return write(nonWhiteChars);
	}
	else
	{
		return *this;
	}
}


AutLib::Ostream& AutLib::OPstream::write(const word& str)
{
	write(char(token::WORD));

	size_t len = str.size();
	writeToBuffer(len);
	writeToBuffer(str.c_str(), len + 1, 1);

	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const string& str)
{
	write(char(token::STRING));

	size_t len = str.size();
	writeToBuffer(len);
	writeToBuffer(str.c_str(), len + 1, 1);

	return *this;
}


AutLib::Ostream& AutLib::OPstream::writeQuoted(const std::string& str, const bool)
{
	write(char(token::STRING));

	size_t len = str.size();
	writeToBuffer(len);
	writeToBuffer(str.c_str(), len + 1, 1);

	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const label val)
{
	write(char(token::LABEL));
	writeToBuffer(val);
	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const floatScalar val)
{
	write(char(token::FLOAT_SCALAR));
	writeToBuffer(val);
	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const doubleScalar val)
{
	write(char(token::DOUBLE_SCALAR));
	writeToBuffer(val);
	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const longDoubleScalar val)
{
	write(char(token::LONG_DOUBLE_SCALAR));
	writeToBuffer(val);
	return *this;
}


AutLib::Ostream& AutLib::OPstream::write(const char* data, std::streamsize count)
{
	if (format() != BINARY)
	{
		FatalErrorIn("Ostream::write(const char*, std::streamsize)")
			<< "stream format not binary"
			<< AutLib::abort(FatalError);
	}

	writeToBuffer(data, count, 8);

	return *this;
}