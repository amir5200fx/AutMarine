#include <IPstream.hxx>

#include <error.hxx>
#include <token.hxx>
#include <cctype>

void AutLib::IPstream::checkEof()
{
	if (bufPosition_ == messageSize_)
	{
		setEof();
	}
}


template<class T>
void AutLib::IPstream::readFromBuffer(T& t)
{
	const size_t align = sizeof(T);
	bufPosition_ = align + ((bufPosition_ - 1) & ~(align - 1));

	t = reinterpret_cast<T&>(buf_[bufPosition_]);
	bufPosition_ += sizeof(T);
	checkEof();
}


void AutLib::IPstream::readFromBuffer
(
	void* data,
	size_t count,
	size_t align
)
{
	if (align > 1)
	{
		bufPosition_ = (int)align + ((bufPosition_ - 1) & ~((int)align - 1));
	}

	const char* bufPtr = &buf_[bufPosition_];
	char* dataPtr = reinterpret_cast<char*>(data);
	size_t i = count;
	while (i--) *dataPtr++ = *bufPtr++;
	bufPosition_ += (int)count;
	checkEof();
}

AutLib::IPstream::~IPstream()
{}

AutLib::Istream& AutLib::IPstream::read(token& t)
{
	// Return the put back token if it exists
	if (Istream::getBack(t))
	{
		return *this;
	}

	char c;

	// return on error
	if (!read(c))
	{
		t.setBad();
		return *this;
	}

	// Set the line number of this token to the current stream line number
	t.lineNumber() = lineNumber();

	// Analyse input starting with this character.
	switch (c)
	{
		// Punctuation
	case token::END_STATEMENT:
	case token::BEGIN_LIST:
	case token::END_LIST:
	case token::BEGIN_SQR:
	case token::END_SQR:
	case token::BEGIN_BLOCK:
	case token::END_BLOCK:
	case token::COLON:
	case token::COMMA:
	case token::ASSIGN:
	case token::ADD:
	case token::SUBTRACT:
	case token::MULTIPLY:
	case token::DIVIDE:
	{
		t = token::punctuationToken(c);
		return *this;
	}

	// Word
	case token::WORD:
	{
		word* pval = new word;
		if (read(*pval))
		{
			if (token::compound::isCompound(*pval))
			{
				t = token::compound::New(*pval, *this).ptr();
				delete pval;
			}
			else
			{
				t = pval;
			}
		}
		else
		{
			delete pval;
			t.setBad();
		}
		return *this;
	}

	// String
	case token::STRING:
	{
		string* pval = new string;
		if (read(*pval))
		{
			t = pval;
		}
		else
		{
			delete pval;
			t.setBad();
		}
		return *this;
	}

	// Label
	case token::LABEL:
	{
		label val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// floatScalar
	case token::FLOAT_SCALAR:
	{
		floatScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// doubleScalar
	case token::DOUBLE_SCALAR:
	{
		doubleScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// longDoubleScalar
	case token::LONG_DOUBLE_SCALAR:
	{
		longDoubleScalar val;
		if (read(val))
		{
			t = val;
		}
		else
		{
			t.setBad();
		}
		return *this;
	}

	// Character (returned as a single character word) or error
	default:
	{
		if (isalpha(c))
		{
			t = word(c);
			return *this;
		}

		setBad();
		t.setBad();

		return *this;
	}
	}
}


AutLib::Istream& AutLib::IPstream::read(char& c)
{
	c = buf_[bufPosition_];
	bufPosition_++;
	checkEof();
	return *this;
}


AutLib::Istream& AutLib::IPstream::read(word& str)
{
	size_t len;
	readFromBuffer(len);
	str = &buf_[bufPosition_];
	bufPosition_ += (int)len + 1;
	checkEof();
	return *this;
}


AutLib::Istream& AutLib::IPstream::read(string& str)
{
	size_t len;
	readFromBuffer(len);
	str = &buf_[bufPosition_];
	bufPosition_ += (int)len + 1;
	checkEof();
	return *this;
}


AutLib::Istream& AutLib::IPstream::read(label& val)
{
	readFromBuffer(val);
	return *this;
}


AutLib::Istream& AutLib::IPstream::read(floatScalar& val)
{
	readFromBuffer(val);
	return *this;
}


AutLib::Istream& AutLib::IPstream::read(doubleScalar& val)
{
	readFromBuffer(val);
	return *this;
}


AutLib::Istream& AutLib::IPstream::read(longDoubleScalar& val)
{
	readFromBuffer(val);
	return *this;
}


AutLib::Istream& AutLib::IPstream::read(char* data, std::streamsize count)
{
	if (format() != BINARY)
	{
		FatalErrorIn("IPstream::read(char*, std::streamsize)")
			<< "stream format not binary"
			<< AutLib::abort(FatalError);
	}

	readFromBuffer(data, count, 8);
	return *this;
}


AutLib::Istream& AutLib::IPstream::rewind()
{
	bufPosition_ = 0;
	return *this;
}