#include <Ostream.hxx>

#include <token.hxx>
#include <keyType.hxx>

// Decrement the indent level
void AutLib::Ostream::decrIndent()
{
	if (indentLevel_ == 0)
	{
		cerr << "Ostream::decrIndent() : attempt to decrement 0 indent level"
			<< std::endl;
	}
	else
	{
		indentLevel_--;
	}
}


// Write keyType
// write regular expression as quoted string
// write plain word as word (unquoted)
AutLib::Ostream& AutLib::Ostream::write(const keyType& kw)
{
	return writeQuoted(kw, kw.isPattern());
}


// Write the keyword followed by appropriate indentation
AutLib::Ostream& AutLib::Ostream::writeKeyword(const keyType& kw)
{
	indent();
	write(kw);

	label nSpaces = entryIndentation_ - label(kw.size());

	// pattern is surrounded by quotes
	if (kw.isPattern())
	{
		nSpaces -= 2;
	}

	// could also increment by indentSize_ ...
	if (nSpaces < 1)
	{
		nSpaces = 1;
	}

	while (nSpaces--)
	{
		write(char(token::SPACE));
	}

	return *this;
}