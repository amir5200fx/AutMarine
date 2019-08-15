#include <regExp.hxx>

#include <List.hxx>

// Alternative regular expression libraries to consider are:
// Boost http://www.boost.org/libs/regex/doc/
// GRETA http://research.microsoft.com/projects/greta/
// Henry Spencer's http://arglist.com/regex/
//
// Chose DEELX http://www.regexlab.com/en/deelx/
// for its ease of integration - one header file
#include "deelx.h"

AutLib::regExp::regExp()
	: preg_(0)
{}


AutLib::regExp::regExp(const char* pattern, const bool ignoreCase)
	: preg_(0)
{
	set(pattern, ignoreCase);
}

AutLib::regExp::regExp(const std::string& pattern, const bool ignoreCase)
	: preg_(0)
{
	set(pattern.c_str(), ignoreCase);
}

AutLib::regExp::~regExp()
{
	clear();
}

void AutLib::regExp::set(const char* pattern, const bool ignoreCase) const
{
	clear();

	// avoid NULL pointer and zero-length patterns
	if (pattern && *pattern)
	{
		int cflags = EXTENDED;
		if (ignoreCase)
		{
			cflags |= IGNORECASE;
		}

		preg_ = new CRegexpT<char>(pattern, cflags);
	}
}


void AutLib::regExp::set(const std::string& pattern, const bool ignoreCase) const
{
	return set(pattern.c_str(), ignoreCase);
}


bool AutLib::regExp::clear() const
{
	if (preg_)
	{
		delete preg_;
		preg_ = 0;

		return true;
	}

	return false;
}


std::string::size_type AutLib::regExp::find(const std::string& str) const
{
	std::string::size_type pos = std::string::npos;

	if (preg_ && !str.empty())
	{
		const MatchResult result = preg_->Match(str.c_str());

		if (0 < result.IsMatched())
		{
			pos = result.GetStart();
		}
	}

	return pos;
}


bool AutLib::regExp::match(const std::string& str) const
{
	bool isExactMatch = false;


	if (preg_ && !str.empty())
	{
		const MatchResult result = preg_->MatchExact(str.c_str());
		isExactMatch = (0 < result.IsMatched());
	}

	return isExactMatch;
}


bool AutLib::regExp::match(const string& str, List<string>& groups) const
{
	bool isMatch = false;

	if (preg_ && !str.empty())
	{
		const MatchResult results = preg_->MatchExact(str.c_str());
		isMatch = (0 < results.IsMatched());

		if (isMatch)
		{
			int const notFound = -1;
			int start, end;
			const int groupsCount = results.MaxGroupNumber();
			groups.setSize(groupsCount);

			for (int i = 0; groupsCount > i; ++i)
			{
				start = results.GetGroupStart(i);
				end = results.GetGroupEnd(i);

				if ((notFound < start) && (notFound < end))
				{
					groups[i] = str.substr(start, end - start);
				}
				else
				{
					groups[i].clear();
				}
			}
		}
	}

	if (!isMatch)
	{
		groups.clear();
	}

	return isMatch;
}

void AutLib::regExp::operator=(const char* pat)
{
	set(pat);
}


void AutLib::regExp::operator=(const std::string& pat)
{
	set(pat);
}