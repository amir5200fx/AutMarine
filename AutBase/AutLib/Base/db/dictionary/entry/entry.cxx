#include <entry.hxx>

#include <dictionary.hxx>
#include <OStringStream.hxx>

AutLib::entry::entry(const keyType& keyword)
	: keyword_(keyword)
{}

AutLib::entry::entry(const entry& e)
	: keyword_(e.keyword_)
{}

AutLib::autoPtr<AutLib::entry> AutLib::entry::clone() const
{
	return clone(dictionary::null);
}

void AutLib::entry::operator=(const entry& e)
{
	// check for assignment to self
	if (this == &e)
	{
		FatalErrorIn("entry::operator=(const entry&)")
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	keyword_ = e.keyword_;
}


bool AutLib::entry::operator==(const entry& e) const
{
	if (keyword_ != e.keyword_)
	{
		return false;
	}
	else
	{
		OStringStream oss1;
		oss1 << *this;

		OStringStream oss2;
		oss2 << e;

		return oss1.str() == oss2.str();
	}
}


bool AutLib::entry::operator!=(const entry& e) const
{
	return !operator==(e);
}