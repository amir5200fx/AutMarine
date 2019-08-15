#include <labelIOList.hxx>

#include <token.hxx>

namespace AutLib
{

	typedef token::Compound<List<label>> tokenCompoundlabelList_;

	template <>
	const word tokenCompoundlabelList_::typeName("List<label>");

	template <>
	debug::debugSwitch tokenCompoundlabelList_::debug(std::string("List<label>"), 0, "");

	token::compound::addIstreamConstructorToTable<token::Compound<List<label>>> addlabelListIstreamConstructorToTable_;;

	template <>
	const word labelIOList::typeName("labelList");

	template <>
	debug::debugSwitch labelIOList::debug(std::string("labelList"), 0, "");

	template <>
	const word labelListIOList::typeName("labelListList");

	template <>
	debug::debugSwitch labelListIOList::debug(std::string("labelListList"), 0, "");
}