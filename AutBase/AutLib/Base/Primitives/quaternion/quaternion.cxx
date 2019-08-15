#include <quaternion.hxx>

#include <IOstreams.hxx>
#include <OStringStream.hxx>

const char* const AutLib::quaternion::typeName = "quaternion";
const AutLib::quaternion AutLib::quaternion::zero(0, vector::zero);
const AutLib::quaternion AutLib::quaternion::I(1, vector::zero);

AutLib::quaternion::quaternion(Istream& is)
{
	operator>>(is, *this);
}

AutLib::word AutLib::name(const quaternion& q)
{
	OStringStream buf;
	buf << '(' << q.w() << ',' << q.v() << ')';
	return buf.str();
}

AutLib::Istream& AutLib::operator>>(Istream& is, quaternion& q)
{
	// Read beginning of quaternion
	is.readBegin("quaternion");

	is >> q.w() >> q.v();

	// Read end of quaternion
	is.readEnd("quaternion");

	// Check state of Istream
	is.check("operator>>(Istream&, quaternion&)");

	return is;
}


AutLib::Ostream& AutLib::operator<<(Ostream& os, const quaternion& q)
{
	os << token::BEGIN_LIST
		<< q.w() << token::SPACE << q.v()
		<< token::END_LIST;

	return os;
}