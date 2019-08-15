#include <IOMap.hxx>

#include <dictionary.hxx>

namespace AutLib
{

	template <>
	const ::AutLib::word IOMap<dictionary>::typeName("IOMap<dictionary>");

	template <>
	::AutLib::debug::debugSwitch IOMap<dictionary>::debug(std::string("IOMap<dictionary>"), 0, "");
}