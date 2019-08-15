#include <autString.hxx>

#include <token.hxx>
#include <Istream.hxx>

AutLib::string::string(Istream& is)
{
	is >> *this;
}

namespace AutLib
{
	Istream& operator>>(Istream& is, string& s)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isString())
		{
			s = t.stringToken();
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, string&)", is)
				<< "wrong token type - expected string found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, string&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const string& s)
	{
		os.write(s);
		os.check("Ostream& operator<<(Ostream&, const string&)");
		return os;
	}


	Ostream& operator<<(Ostream& os, const std::string& s)
	{
		os.write(string(s));
		os.check("Ostream& operator<<(Ostream&, const std::string&)");
		return os;
	}
}