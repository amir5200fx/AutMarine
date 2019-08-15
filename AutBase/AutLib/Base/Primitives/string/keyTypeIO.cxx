#include <keyType.hxx>

#include <token.hxx>
#include <error.hxx>
#include <Istream.hxx>

AutLib::keyType::keyType(Istream& is)
	: word()
{
	is >> *this;
}

namespace AutLib
{

	Istream& operator>>(Istream& is, keyType& w)
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
			// Assign from string. Sets regular expression.
			w = t.stringToken();
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, keyType&)", is)
				<< "wrong token type - expected word or string found "
				<< t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of IOstream
		is.check("Istream& operator>>(Istream&, keyType&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const keyType& w)
	{
		os.write(w);
		os.check("Ostream& operator<<(Ostream&, const keyType&)");
		return os;
	}
}