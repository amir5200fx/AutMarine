#include <complex.hxx>

#include <Istream.hxx>
#include <Ostream.hxx>
#include <token.hxx>

#include <sstream>

const char* const AutLib::complex::typeName = "complex";
const AutLib::complex AutLib::complex::zero(0, 0);
const AutLib::complex AutLib::complex::one(1, 1);

AutLib::complex::complex(Istream& is)
{
	is >> *this;
}

AutLib::word AutLib::name(const complex& c)
{
	std::ostringstream buf;
	buf << '(' << c.Re() << ',' << c.Im() << ')';
	return buf.str();
}

namespace AutLib
{

	Istream& operator>>(Istream& is, complex& c)
	{
		// Read beginning of complex
		is.readBegin("complex");

		is >> c.re >> c.im;

		// Read end of complex
		is.readEnd("complex");

		// Check state of Istream
		is.check("operator>>(Istream&, complex&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const complex& c)
	{
		os << token::BEGIN_LIST
			<< c.re << token::SPACE << c.im
			<< token::END_LIST;

		return os;
	}
}