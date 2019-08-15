#include <word.hxx>

#include <token.hxx>
#include <Istream.hxx>

AutLib::word::word(Istream& is)
	: string()
{
	is >> *this;
}


namespace AutLib
{
	Istream& operator>>(Istream& is, word& w)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isWord())
		{
			w = t.wordToken();
		}
		else if (t.isString())
		{
			// try a bit harder and convert string to word
			w = t.stringToken();
			string::stripInvalid<word>(w);

			// flag empty strings and bad chars as an error
			if (w.empty() || w.size() != t.stringToken().size())
			{
				is.setBad();
				FatalIOErrorIn("operator>>(Istream&, word&)", is)
					<< "wrong token type - expected word found non-word characters "
					<< t.info()
					<< exit(FatalIOError);
				return is;
			}
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, word&)", is)
				<< "wrong token type - expected word found "
				<< t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of IOstream
		is.check("Istream& operator>>(Istream&, word&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const word& w)
	{
		os.write(w);
		os.check("Ostream& operator<<(Ostream&, const word&)");
		return os;
	}
}