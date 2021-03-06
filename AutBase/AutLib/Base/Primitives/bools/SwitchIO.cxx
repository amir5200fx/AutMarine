#include <Switch.hxx>

#include <token.hxx>
#include <Istream.hxx>

AutLib::Switch::Switch(Istream& is)
{
	is >> *this;
}

namespace AutLib
{
	Istream& operator>>(Istream& is, Switch& s)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isLabel())
		{
			s = bool(t.labelToken());
		}
		else if (t.isWord())
		{
			// allow invalid values, but catch after for correct error message
			Switch sw(t.wordToken(), true);

			if (sw.valid())
			{
				s = sw;
			}
			else
			{
				is.setBad();
				FatalIOErrorIn("operator>>(Istream&, bool/Switch&)", is)
					<< "expected 'true/false', 'on/off' ... found " << t.wordToken()
					<< exit(FatalIOError);

				return is;
			}
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, bool/Switch&)", is)
				<< "wrong token type - expected bool, found " << t
				<< exit(FatalIOError);

			return is;
		}


		// Check state of Istream
		is.check("Istream& operator>>(Istream&, Switch&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const Switch& s)
	{
		os << Switch::names[s.switch_];
		os.check("Ostream& operator<<(Ostream&, const Switch&)");
		return os;
	}
}