#include <timeSelector.hxx>

#include <instantList.hxx>
#include <ListOps.hxx>
#include <argList.hxx>
#include <autTime.hxx>

AutLib::timeSelector::timeSelector()
	: scalarRanges()
{}


AutLib::timeSelector::timeSelector(Istream& is)
	: scalarRanges(is)
{}

bool AutLib::timeSelector::selected(const instant& value) const
{
	return scalarRanges::selected(value.value());
}


AutLib::List<bool> AutLib::timeSelector::selected(const List<instant>& Times) const
{
	List<bool> lst(Times.size(), false);

	// check ranges, avoid false positive on constant/
	for (AutLib::label timeI = 0; timeI < (Times).size(); timeI++)
	{
		if (Times[timeI].name() != "constant" && selected(Times[timeI]))
		{
			lst[timeI] = true;
		}
	}

	// check specific values
	for (AutLib::label rangeI = 0; rangeI < (*this).size(); rangeI++)
	{
		if (operator[](rangeI).isExact())
		{
			scalar target = operator[](rangeI).value();

			int nearestIndex = -1;
			scalar nearestDiff = AutLib::GREAT;

			for (AutLib::label timeI = 0; timeI < (Times).size(); timeI++)
			{
				if (Times[timeI].name() == "constant") continue;

				scalar diff = fabs(Times[timeI].value() - target);
				if (diff < nearestDiff)
				{
					nearestDiff = diff;
					nearestIndex = timeI;
				}
			}

			if (nearestIndex >= 0)
			{
				lst[nearestIndex] = true;
			}
		}
	}

	return lst;
}


AutLib::List<AutLib::instant> AutLib::timeSelector::select
(
	const List<instant>& Times
) const
{
	return subset(selected(Times), Times);
}


void AutLib::timeSelector::inplaceSelect
(
	List<instant>& Times
) const
{
	inplaceSubset(selected(Times), Times);
}


void AutLib::timeSelector::addOptions
(
	const bool constant,
	const bool zeroTime
)
{
	if (constant)
	{
		argList::validOptions.insert("constant", "");
	}
	if (zeroTime)
	{
		argList::validOptions.insert("zeroTime", "");
	}
	argList::validOptions.insert("noZero", "");
	argList::validOptions.insert("time", "ranges");
	argList::validOptions.insert("latestTime", "");
}

AutLib::List<AutLib::instant> AutLib::timeSelector::select
(
	const List<instant>& timeDirs,
	const argList& args
)
{
	if (timeDirs.size())
	{
		List<bool> selectTimes(timeDirs.size(), true);

		// determine locations of constant/ and 0/ directories
		label constantIdx = -1;
		label zeroIdx = -1;

		for (AutLib::label timeI = 0; timeI < (timeDirs).size(); timeI++)
		{
			if (timeDirs[timeI].name() == "constant")
			{
				constantIdx = timeI;
			}
			else if (timeDirs[timeI].value() == 0)
			{
				zeroIdx = timeI;
			}

			if (constantIdx >= 0 && zeroIdx >= 0)
			{
				break;
			}
		}

		// determine latestTime selection (if any)
		// this must appear before the -time option processing
		label latestIdx = -1;
		if (args.optionFound("latestTime"))
		{
			selectTimes = false;
			latestIdx = timeDirs.size() - 1;

			// avoid false match on constant/
			if (latestIdx == constantIdx)
			{
				latestIdx = -1;
			}
		}

		if (args.optionFound("time"))
		{
			// can match 0/, but can never match constant/
			selectTimes = timeSelector
			(
				args.optionLookup("time")()
			).selected(timeDirs);
		}


		// add in latestTime (if selected)
		if (latestIdx >= 0)
		{
			selectTimes[latestIdx] = true;
		}

		if (constantIdx >= 0)
		{
			// only add constant/ if specifically requested
			selectTimes[constantIdx] = args.optionFound("constant");
		}

		// special treatment for 0/
		if (zeroIdx >= 0)
		{
			if (args.optionFound("noZero"))
			{
				// exclude 0/ if specifically requested
				selectTimes[zeroIdx] = false;
			}
			else if (argList::validOptions.found("zeroTime"))
			{
				// with -zeroTime enabled, drop 0/ unless specifically requested
				selectTimes[zeroIdx] = args.optionFound("zeroTime");
			}
		}

		return subset(selectTimes, timeDirs);
	}
	else
	{
		return timeDirs;
	}
}


AutLib::List<AutLib::instant> AutLib::timeSelector::select0
(
	Time& runTime,
	const argList& args
)
{
	instantList timeDirs = timeSelector::select(runTime.times(), args);

	if (timeDirs.empty())
	{
		FatalErrorIn(args.executable())
			<< "No times selected"
			<< exit(FatalError);
	}

	runTime.setTime(timeDirs[0], 0);

	return timeDirs;
}