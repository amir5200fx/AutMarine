#include <bool.hxx>

const char* const AutLib::pTraits<bool>::typeName = "bool";
const bool AutLib::pTraits<bool>::zero(false);
const bool AutLib::pTraits<bool>::one(true);

const char* AutLib::pTraits<bool>::componentNames[] = { "x" };

AutLib::pTraits<bool>::pTraits(Istream& is)
{
	is >> p_;
}