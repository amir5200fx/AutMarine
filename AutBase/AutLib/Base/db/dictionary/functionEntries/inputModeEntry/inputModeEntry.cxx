#include <inputModeEntry.hxx>

const AutLib::word AutLib::functionEntries::inputModeEntry::typeName
(
	AutLib::functionEntries::inputModeEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include inputModeEntries
AutLib::debug::debugSwitch
AutLib::functionEntries::inputModeEntry::debug
(
	"inputModeEntry",
	0
);

AutLib::functionEntries::inputModeEntry::inputMode
AutLib::functionEntries::inputModeEntry::mode_(MERGE);

namespace AutLib
{
	namespace functionEntries
	{
		/* Add the inputModeEntry execute to the table */
		functionEntry::addexecutedictionaryIstreamMemberFunctionToTable<inputModeEntry>
			addinputModeEntryexecutedictionaryIstreamMemberFunctionTofunctionEntryTable_;
	}
}

// we could combine this into execute() directly, but leave it here for now
void AutLib::functionEntries::inputModeEntry::setMode(Istream& is)
{
	clear();

	word mode(is);
	if (mode == "merge" || mode == "default")
	{
		mode_ = MERGE;
	}
	else if (mode == "overwrite")
	{
		mode_ = OVERWRITE;
	}
	else if (mode == "protect")
	{
		mode_ = PROTECT;
	}
	else if (mode == "warn")
	{
		mode_ = WARN;
	}
	else if (mode == "error")
	{
		mode_ = FATALERROR;
	}
	else
	{
		WarningIn("AutLib::functionEntries::inputModeEntry::setMode(Istream&)")
			<< "unsupported input mode '" << mode
			<< "' ... defaulting to 'merge'"
			<< endl;
	}
}

bool AutLib::functionEntries::inputModeEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	setMode(is);
	return true;
}


void AutLib::functionEntries::inputModeEntry::clear()
{
	mode_ = MERGE;
}


bool AutLib::functionEntries::inputModeEntry::merge()
{
	return mode_ == MERGE;
}


bool AutLib::functionEntries::inputModeEntry::overwrite()
{
	return mode_ == OVERWRITE;
}


bool AutLib::functionEntries::inputModeEntry::protect()
{
	return mode_ == PROTECT;
}

bool AutLib::functionEntries::inputModeEntry::error()
{
	return mode_ == FATALERROR;
}