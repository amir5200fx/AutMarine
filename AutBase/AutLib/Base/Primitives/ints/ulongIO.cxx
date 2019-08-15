#include <ulong.hxx>

#include <token.hxx>
#include <Istream.hxx>

#include <sstream>

AutLib::word AutLib::name(const unsigned long val)
{
	std::ostringstream buf;
	buf << val;
	return buf.str();
}

unsigned long AutLib::readUlong(Istream& is)
{
	unsigned long val;
	is >> val;

	return val;
}

namespace AutLib
{

	Istream& operator>>(Istream& is, unsigned long& val)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isLabel())
		{
			val = static_cast<unsigned long>(t.labelToken());
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, unsigned long&)", is)
				<< "wrong token type - expected unsigned long found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, unsigned long&)");

		return is;
	}

	Ostream& operator<<(Ostream& os, const unsigned long val)
	{
		os.write(label(val));
		os.check("Ostream& operator<<(Ostream&, const unsigned long)");
		return os;
	}
}