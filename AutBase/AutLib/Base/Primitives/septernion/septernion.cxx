#include <septernion.hxx>

#include <IOstreams.hxx>
#include <OStringStream.hxx>

const char* const AutLib::septernion::typeName = "septernion";
const AutLib::septernion AutLib::septernion::zero(vector::zero, quaternion::zero);
const AutLib::septernion AutLib::septernion::I(vector::zero, quaternion::I);

AutLib::septernion::septernion(Istream& is)
{
	operator>>(is, *this);
}

AutLib::word AutLib::name(const septernion& s)
{
	OStringStream buf;
	buf << '(' << s.t() << ',' << s.r() << ')';
	return buf.str();
}

AutLib::Istream& AutLib::operator>>(Istream& is, septernion& s)
{
	// Read beginning of septernion
	is.readBegin("septernion");

	is >> s.t() >> s.r();

	// Read end of septernion
	is.readEnd("septernion");

	// Check state of Istream
	is.check("operator>>(Istream&, septernion&)");

	return is;
}


AutLib::Ostream& AutLib::operator<<(Ostream& os, const septernion& s)
{
	os << token::BEGIN_LIST
		<< s.t() << token::SPACE << s.r()
		<< token::END_LIST;

	return os;
}