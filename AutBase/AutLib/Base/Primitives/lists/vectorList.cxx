#include <vectorList.hxx>

namespace AutLib
{

	typedef token::Compound<List<vector>> tokenCompoundvectorList_;

	template <>
	const ::AutLib::word tokenCompoundvectorList_::typeName("List<vector>");

	template <>
	::AutLib::debug::debugSwitch tokenCompoundvectorList_::debug(std::string("List<vector>"), 0, "");

	token::compound::addIstreamConstructorToTable<token::Compound<List<vector>>> addvectorListIstreamConstructorToTable_;;
}