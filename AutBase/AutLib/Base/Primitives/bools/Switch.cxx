#include <Switch.hxx>

#include <dictionary.hxx>

// NB: values chosen such that bitwise '&' 0x1 yields the bool value
// INVALID is also evaluates to false, but don't rely on that
const char* AutLib::Switch::names[AutLib::Switch::INVALID + 1] =
{
	"false", "true",
	"off",   "on",
	"no",    "yes",
	"n",     "y",
	"f",     "t",
	"none",  "true",  // is there a reasonable counterpart to "none"?
	"invalid"
};

AutLib::Switch::switchType AutLib::Switch::asEnum
(
	const std::string& str,
	const bool allowInvalid
)
{
	for (int sw = 0; sw < Switch::INVALID; ++sw)
	{
		if (str == names[sw])
		{
			// handle aliases
			switch (sw)
			{
			case Switch::NO_1:
			case Switch::NONE:
			{
				return Switch::NO;
				break;
			}

			case Switch::YES_1:
			{
				return Switch::YES;
				break;
			}

			case Switch::FALSE_1:
			{
				return Switch::FALSE;
				break;
			}

			case Switch::TRUE_1:
			{
				return Switch::TRUE;
				break;
			}

			default:
			{
				return switchType(sw);
				break;
			}
			}
		}
	}

	if (!allowInvalid)
	{
		FatalErrorIn("Switch::asEnum(const std::string&, const bool)")
			<< "unknown switch word " << str << nl
			<< abort(FatalError);
	}

	return Switch::INVALID;
}

AutLib::Switch AutLib::Switch::lookupOrAddToDict
(
	const word& name,
	dictionary& dict,
	const Switch& defaultValue
)
{
	return dict.lookupOrAddDefault<Switch>(name, defaultValue);
}

bool AutLib::Switch::valid() const
{
	return switch_ <= Switch::NONE;
}


const char* AutLib::Switch::asText() const
{
	return names[switch_];
}


bool AutLib::Switch::readIfPresent(const word& name, const dictionary& dict)
{
	return dict.readIfPresent<Switch>(name, *this);
}