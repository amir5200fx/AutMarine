#include <bool.hxx>

#include <Switch.hxx>
#include <Istream.hxx>
#include <Ostream.hxx>

bool AutLib::readBool(Istream& is)
{
	bool val;
	is >> val;

	return val;
}

namespace AutLib
{

	Istream& operator>>(Istream& is, bool& b)
	{
		if (is.good())
		{
			b = Switch(is);
		}

		return is;
	}


	Ostream& operator<<(Ostream& os, const bool b)
	{
		// we could also write as text string without any difficulty
		// os << Switch::asText(b);
		os.write(label(b));
		os.check("Ostream& operator<<(Ostream&, const bool)");
		return os;
	}
}