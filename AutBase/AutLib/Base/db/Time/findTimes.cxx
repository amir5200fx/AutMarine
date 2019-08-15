#include <autTime.hxx>

#include <fileNameList.hxx>
#include <OSspecific.hxx>

AutLib::instantList AutLib::Time::findTimes(const fileName& directory)
{
	if (debug)
	{
		Info << "Time::findTimes(const fileName&): finding times in directory "
			<< directory << endl;
	}

	// Read directory entries into a list
	fileNameList dirEntries(readDir(directory, fileName::DIRECTORY));

	// Initialise instant list
	instantList Times(dirEntries.size() + 1);
	label nTimes = 0;

	// Check for "constant"
	bool haveConstant = false;
	for (label i = 0; i < (dirEntries).size(); i++)
	{
		if (dirEntries[i] == "constant")
		{
			Times[nTimes].value() = 0;
			Times[nTimes].name() = dirEntries[i];
			nTimes++;
			haveConstant = true;
			break;
		}
	}

	// Read and parse all the entries in the directory
	for (label i = 0; i < (dirEntries).size(); i++)
	{
		IStringStream timeStream(dirEntries[i]);
		token timeToken(timeStream);

		if (timeToken.isNumber() && timeStream.eof())
		{
			Times[nTimes].value() = timeToken.number();
			Times[nTimes].name() = dirEntries[i];
			nTimes++;
		}
	}

	// Reset the length of the times list
	Times.setSize(nTimes);

	if (haveConstant)
	{
		if (nTimes > 2)
		{
			std::sort(&Times[1], Times.end(), instant::less());
		}
	}
	else if (nTimes > 1)
	{
		std::sort(&Times[0], Times.end(), instant::less());
	}

	return Times;
}