#include <ITstream.hxx>

#include <error.hxx>
#include <OSstream.hxx>

void AutLib::ITstream::print(Ostream& os) const
{
	os << "ITstream : " << name_.c_str();

	if (size())
	{
		if (begin()->lineNumber() == rbegin()->lineNumber())
		{
			os << ", line " << begin()->lineNumber() << ", ";
		}
		else
		{
			os << ", lines " << begin()->lineNumber()
				<< '-' << rbegin()->lineNumber() << ", ";
		}
	}
	else
	{
		os << ", line " << lineNumber() << ", ";
	}

	IOstream::print(os);
}


AutLib::Istream& AutLib::ITstream::read(token& t)
{
	// Return the put back token if it exists
	if (Istream::getBack(t))
	{
		lineNumber_ = t.lineNumber();
		return *this;
	}

	if (tokenIndex_ < size())
	{
		t = operator[](tokenIndex_++);
		lineNumber_ = t.lineNumber();

		if (tokenIndex_ == size())
		{
			setEof();
		}
	}
	else
	{
		if (eof())
		{
			FatalIOErrorIn
			(
				"ITstream::read(token& t)",
				*this
			) << "attempt to read beyond EOF"
				<< exit(FatalIOError);

			setBad();
		}
		else
		{
			setEof();
		}

		if (size())
		{
			token::undefinedToken.lineNumber()
				= operator[](size() - 1).lineNumber();
		}
		else
		{
			token::undefinedToken.lineNumber() = lineNumber();
		}

		t = token::undefinedToken;
	}

	return *this;
}


AutLib::Istream& AutLib::ITstream::read(char&)
{
	notImplemented("Istream& ITstream::read(char& c)");
	return *this;
}


AutLib::Istream& AutLib::ITstream::read(word&)
{
	notImplemented("Istream& ITstream::read(word&)");
	return *this;
}


AutLib::Istream& AutLib::ITstream::read(string&)
{
	notImplemented("Istream& ITstream::read(string&)");
	return *this;
}


AutLib::Istream& AutLib::ITstream::read(label&)
{
	notImplemented("Istream& ITstream::read(label&)");
	return *this;
}


AutLib::Istream& AutLib::ITstream::read(floatScalar&)
{
	notImplemented("Istream& ITstream::read(floatScalar&)");
	return *this;
}


AutLib::Istream& AutLib::ITstream::read(doubleScalar&)
{
	notImplemented("Istream& ITstream::read(doubleScalar&)");
	return *this;
}


AutLib::Istream& AutLib::ITstream::read(longDoubleScalar&)
{
	notImplemented("Istream& ITstream::read(longDoubleScalar&)");
	return *this;
}


AutLib::Istream& AutLib::ITstream::read(char*, std::streamsize)
{
	notImplemented("Istream& ITstream::read(char*, std::streamsize)");
	return *this;
}


// Rewind the token stream so that it may be read again
AutLib::Istream& AutLib::ITstream::rewind()
{
	tokenIndex_ = 0;

	if (size())
	{
		lineNumber_ = operator[](0).lineNumber();
	}

	setGood();

	return *this;
}