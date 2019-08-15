#include <int.hxx>

#include <error.hxx>
#include <token.hxx>
#include <Istream.hxx>

#include <sstream>

AutLib::word AutLib::name(const int val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}

int AutLib::readInt(Istream& is)
{
	int val;
	is >> val;

	return val;
}

namespace AutLib
{

	Istream& operator>>(Istream& is, int& i)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isLabel())
		{
			i = int(t.labelToken());
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, int&)", is)
				<< "wrong token type - expected int found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, int&)");

		return is;
	}

	Ostream& operator<<(Ostream& os, const int i)
	{
		os.write(label(i));
		os.check("Ostream& operator<<(Ostream&, const int)");
		return os;
	}
}