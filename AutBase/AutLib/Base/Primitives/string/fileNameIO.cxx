#include <fileName.hxx>

#include <Istream.hxx>
#include <Ostream.hxx>

AutLib::fileName::fileName(Istream& is)
	: string(is)
{
	stripInvalid();
}


namespace AutLib
{
	Istream& operator>>(Istream& is, fileName& fn)
	{
		fileName fName(is);

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, fileName&)");

		fn = fName;

		return is;
	}


	Ostream& operator<<(Ostream& os, const fileName& fn)
	{
		os.write(fn);
		os.check("Ostream& operator<<(Ostream&, const fileName&)");
		return os;
	}
}