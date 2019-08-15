#include <JobInfo.hxx>

#include <Pstream.hxx>
#include <OSspecific.hxx>
#include <OFstream.hxx>
#include <clock.hxx>

AutLib::debug::infoSwitch
AutLib::JobInfo::writeJobInfo
(
	"writeJobInfo",
	0
);

bool AutLib::JobInfo::constructed = true;
AutLib::JobInfo AutLib::jobInfo;

AutLib::JobInfo::JobInfo()
	: runningJobPath_()
	, finishedJobPath_()
	, cpuTime_()
{
	name() = "JobInfo";

	if (writeJobInfo && Pstream::master())
	{
		string baseDir = getEnv("FOAM_JOB_DIR");
		string jobFile = hostName() + '.' + AutLib::name(pid());

		fileName runningDir(baseDir / "runningJobs");
		fileName finishedDir(baseDir / "finishedJobs");

		runningJobPath_ = runningDir / jobFile;
		finishedJobPath_ = finishedDir / jobFile;

		if (baseDir.empty())
		{
			FatalErrorIn("JobInfo::JobInfo()")
				<< "Cannot get JobInfo directory $FOAM_JOB_DIR"
				<< AutLib::exit(FatalError);
		}

		if (!isDir(runningDir) && !mkDir(runningDir))
		{
			FatalErrorIn("JobInfo::JobInfo()")
				<< "Cannot make JobInfo directory " << runningDir
				<< AutLib::exit(FatalError);
		}

		if (!isDir(finishedDir) && !mkDir(finishedDir))
		{
			FatalErrorIn("JobInfo::JobInfo()")
				<< "Cannot make JobInfo directory " << finishedDir
				<< AutLib::exit(FatalError);
		}
	}

	constructed = true;
}

AutLib::JobInfo::~JobInfo()
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		mv(runningJobPath_, finishedJobPath_);
	}

	constructed = false;
}

bool AutLib::JobInfo::write(Ostream& os) const
{
	if (writeJobInfo && Pstream::master())
	{
		if (os.good())
		{
			dictionary::write(os, false);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}


void AutLib::JobInfo::write() const
{
	if (writeJobInfo && Pstream::master())
	{
		if (!write(OFstream(runningJobPath_)()))
		{
			FatalErrorIn("JobInfo::write() const")
				<< "Failed to write to JobInfo file "
				<< runningJobPath_
				<< AutLib::exit(FatalError);
		}
	}
}


void AutLib::JobInfo::end(const word& terminationType)
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		add("cpuTime", cpuTime_.elapsedCpuTime());
		add("endDate", clock::date());
		add("endTime", clock::clockTime());

		if (!found("termination"))
		{
			add("termination", terminationType);
		}

		rm(runningJobPath_);
		write(OFstream(finishedJobPath_)());
	}

	constructed = false;
}


void AutLib::JobInfo::end()
{
	end("normal");
}


void AutLib::JobInfo::exit()
{
	end("exit");
}


void AutLib::JobInfo::abort()
{
	end("abort");
}


void AutLib::JobInfo::signalEnd() const
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		mv(runningJobPath_, finishedJobPath_);
	}

	constructed = false;
}