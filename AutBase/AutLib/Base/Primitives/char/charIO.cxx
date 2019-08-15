#include <char.hxx>

#include <Istream.hxx>
#include <Ostream.hxx>

char AutLib::readChar(Istream& is)
{
	char c;
	is.read(c);
	return c;
}

namespace AutLib
{

	Istream& operator>>(Istream& is, char& c)
	{
		is.read(c);
		is.check("Istream& operator>>(Istream&, char&)");
		return is;
	}


	Ostream& operator<<(Ostream& os, const char c)
	{
		os.write(c);
		os.check("Ostream& operator<<(Ostream&, const char)");
		return os;
	}

	Ostream& operator<<(Ostream& os, const char* s)
	{
		os.write(s);
		os.check("Ostream& operator<<(Ostream&, const char*)");
		return os;
	}
}