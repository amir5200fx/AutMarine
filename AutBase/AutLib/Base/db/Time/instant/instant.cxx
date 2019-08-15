#include <instant.hxx>

#include <autTime.hxx>

const char* const AutLib::instant::typeName = "instant";

AutLib::instant::instant()
{}

AutLib::instant::instant(const scalar val, const word& tname)
	: value_(val)
	, name_(tname)
{
}

AutLib::instant::instant(const scalar val)
	: value_(val)
	, name_(Time::timeName(val))
{}

AutLib::instant::instant(const word& tname)
	: value_(atof(tname.c_str()))
	, name_(tname)
{}

bool AutLib::operator==(const instant& a, const instant& b)
{
	return
		(
			a.value_ < b.value_ + SMALL
			&& a.value_ > b.value_ - SMALL
			);
}


bool AutLib::operator!=(const instant& a, const instant& b)
{
	return !operator==(a, b);
}

AutLib::Istream& AutLib::operator>>(Istream& is, instant& I)
{
	is >> I.value_ >> I.name_;

	return is;
}


AutLib::Ostream& AutLib::operator<<(Ostream& os, const instant& I)
{
	os << I.value_ << tab << I.name_;

	return os;
}