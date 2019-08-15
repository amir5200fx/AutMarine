#include <autTime.hxx>

#include <Pstream.hxx>
#include <PstreamReduceOps.hxx>
#include <profilingPool.hxx>
#include <profilingTrigger.hxx>

const ::AutLib::word AutLib::Time::typeName(AutLib::Time::typeName_());
::AutLib::debug::debugSwitch AutLib::Time::debug(std::string(AutLib::Time::typeName_()), 0, "");;

template<>
const char* AutLib::NamedEnum<AutLib::Time::stopAtControls, 4>::names[] =
{
	"endTime",
	"noWriteNow",
	"writeNow",
	"nextWrite"
};

const AutLib::NamedEnum<AutLib::Time::stopAtControls, 4>
AutLib::Time::stopAtControlNames_;

template<>
const char* AutLib::NamedEnum<AutLib::Time::writeControls, 5>::names[] =
{
	"timeStep",
	"runTime",
	"adjustableRunTime",
	"clockTime",
	"cpuTime"
};

const AutLib::NamedEnum<AutLib::Time::writeControls, 5>
AutLib::Time::writeControlNames_;

AutLib::Time::fmtflags AutLib::Time::format_(AutLib::Time::general);
int AutLib::Time::precision_(6);

AutLib::word AutLib::Time::controlDictName("controlDict");

void AutLib::Time::adjustDeltaT()
{
	if (writeControl_ == wcAdjustableRunTime)
	{
		scalar timeToNextWrite = max
		(
			scalar(0),
			(outputTimeIndex_ + 1)*writeInterval_ - (value() - startTime_)
		);

		label nStepsToNextWrite = label(timeToNextWrite / deltaT_ - SMALL) + 1;
		scalar newDeltaT = timeToNextWrite / nStepsToNextWrite;

		// Control the increase of the time step to within a factor of 2
		// and the decrease within a factor of 5.
		if (newDeltaT >= deltaT_)
		{
			deltaT_ = min(newDeltaT, 2.0*deltaT_);
		}
		else
		{
			deltaT_ = max(newDeltaT, 0.2*deltaT_);
		}
	}
}


void AutLib::Time::setControls()
{
	// default is to resume calculation from "latestTime"
	word startFrom = controlDict_.lookupOrDefault<word>
		(
			"startFrom",
			"latestTime"
			);

	if (startFrom == "startTime")
	{
		controlDict_.lookup("startTime") >> startTime_;
	}
	else
	{
		// Search directory for valid time directories
		instantList timeDirs = findTimes(path());

		if (startFrom == "firstTime")
		{
			if (timeDirs.size())
			{
				startTime_ = timeDirs[0].value();
			}
		}
		else if (startFrom == "latestTime")
		{
			if (timeDirs.size())
			{
				startTime_ = timeDirs[timeDirs.size() - 1].value();
			}
		}
		else
		{
			FatalIOErrorIn("Time::setControls()", controlDict_)
				<< "expected startTime, firstTime or latestTime"
				<< " found '" << startFrom << "'"
				<< exit(FatalIOError);
		}
	}

	setTime(startTime_, 0);

	readDict();
	deltaTSave_ = deltaT_;
	deltaT0_ = deltaTSave_;

	if (Pstream::parRun())
	{
		scalar sumStartTime = startTime_;
		reduce(sumStartTime, sumOp<scalar>());
		if
			(
				mag(Pstream::nProcs()*startTime_ - sumStartTime)
		  > Pstream::nProcs()*deltaT_ / 10.0
				)
		{
			FatalIOErrorIn("Time::setControls()", controlDict_)
				<< "Start time is not the same for all processors" << nl
				<< "processor " << Pstream::myProcNo() << " has startTime "
				<< startTime_ << exit(FatalIOError);
		}
	}

	IOdictionary timeDict
	(
		IOobject
		(
			"time",
			timeName(),
			"uniform",
			*this,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE,
			false
		)
	);

	if (timeDict.readIfPresent("deltaT", deltaTSave_))
	{
		deltaT0_ = deltaTSave_;
	}

	if (timeDict.readIfPresent("index", startTimeIndex_))
	{
		timeIndex_ = startTimeIndex_;
	}
}

AutLib::Time::Time
(
	const word& controlDictName,
	const fileName& rootPath,
	const fileName& caseName,
	const word& systemName,
	const word& constantName,
	const bool enableFunctionObjects
)
	:
	TimePaths
	(
		rootPath,
		caseName,
		systemName,
		constantName
	),

	objectRegistry(*this),

	controlDict_
	(
		IOobject
		(
			controlDictName,
			system(),
			*this,
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		)
	),

	startTimeIndex_(0),
	startTime_(0),
	endTime_(0),

	stopAt_(saEndTime),
	writeControl_(wcTimeStep),
	writeInterval_(GREAT),
	purgeWrite_(0),
	subCycling_(false),

	writeFormat_(IOstream::ASCII),
	writeVersion_(IOstream::currentVersion),
	writeCompression_(IOstream::UNCOMPRESSED),
	graphFormat_("raw"),
	runTimeModifiable_(true),

	readLibs_(controlDict_, "libs"),
	functionObjects_(*this, enableFunctionObjects)
{
	setControls();

	profilingPool::initProfiling
	(
		IOobject
		(
			"profilingInfo",
			timeName(),
			"uniform",
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		*this
	);
}


AutLib::Time::Time
(
	const dictionary& dict,
	const fileName& rootPath,
	const fileName& caseName,
	const word& systemName,
	const word& constantName,
	const bool enableFunctionObjects
)
	:
	TimePaths
	(
		rootPath,
		caseName,
		systemName,
		constantName
	),

	objectRegistry(*this),

	controlDict_
	(
		IOobject
		(
			controlDictName,
			system(),
			*this,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		dict
	),

	startTimeIndex_(0),
	startTime_(0),
	endTime_(0),

	stopAt_(saEndTime),
	writeControl_(wcTimeStep),
	writeInterval_(GREAT),
	purgeWrite_(0),
	subCycling_(false),

	writeFormat_(IOstream::ASCII),
	writeVersion_(IOstream::currentVersion),
	writeCompression_(IOstream::UNCOMPRESSED),
	graphFormat_("raw"),
	runTimeModifiable_(true),

	readLibs_(controlDict_, "libs"),
	functionObjects_(*this, enableFunctionObjects)
{
	setControls();

	profilingPool::initProfiling
	(
		IOobject
		(
			"profilingInfo",
			timeName(),
			"uniform",
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		*this
	);
}


AutLib::Time::Time
(
	const fileName& rootPath,
	const fileName& caseName,
	const word& systemName,
	const word& constantName,
	const bool enableFunctionObjects
)
	:
	TimePaths
	(
		rootPath,
		caseName,
		systemName,
		constantName
	),

	objectRegistry(*this),

	controlDict_
	(
		IOobject
		(
			controlDictName,
			system(),
			*this,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	),

	startTimeIndex_(0),
	startTime_(0),
	endTime_(0),

	stopAt_(saEndTime),
	writeControl_(wcTimeStep),
	writeInterval_(GREAT),
	purgeWrite_(0),
	subCycling_(false),

	writeFormat_(IOstream::ASCII),
	writeVersion_(IOstream::currentVersion),
	writeCompression_(IOstream::UNCOMPRESSED),
	graphFormat_("raw"),
	runTimeModifiable_(true),

	readLibs_(controlDict_, "libs"),
	functionObjects_(*this, enableFunctionObjects)
{
	profilingPool::initProfiling
	(
		IOobject
		(
			"profilingInfo",
			timeName(),
			"uniform",
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		*this
	);
}

AutLib::Time::~Time()
{
	// destroy function objects first
	functionObjects_.clear();

	profilingPool::stopProfiling(*this);
}

AutLib::word AutLib::Time::timeName(const scalar t)
{
	std::ostringstream buf;
	buf.setf(ios_base::fmtflags(format_), ios_base::floatfield);
	buf.precision(precision_);
	buf << t;
	return buf.str();
}


AutLib::word AutLib::Time::timeName() const
{
	return dimensionedScalar::name();
}


// Search the construction path for times
AutLib::instantList AutLib::Time::times() const
{
	return findTimes(path());
}


AutLib::word AutLib::Time::findInstancePath(const instant& t) const
{
	instantList timeDirs = findTimes(path());

	for (label timeI = (timeDirs).size() - 1; timeI >= 0; timeI--)
	{
		if (timeDirs[timeI] == t)
		{
			return timeDirs[timeI].name();
		}
	}

	return word::null;
}


AutLib::instant AutLib::Time::findClosestTime(const scalar t) const
{
	instantList timeDirs = findTimes(path());

	// there is only one time (likely "constant") so return it
	if (timeDirs.size() == 1)
	{
		return timeDirs[0];
	}

	if (t < timeDirs[1].value())
	{
		return timeDirs[1];
	}
	else if (t > timeDirs[timeDirs.size() - 1].value())
	{
		return timeDirs[timeDirs.size() - 1];
	}

	label nearestIndex = -1;
	scalar deltaT = GREAT;

	for (label timeI = 1; timeI < timeDirs.size(); ++timeI)
	{
		scalar diff = mag(timeDirs[timeI].value() - t);
		if (diff < deltaT)
		{
			deltaT = diff;
			nearestIndex = timeI;
		}
	}

	return timeDirs[nearestIndex];
}

// This should work too,
// if we don't worry about checking "constant" explicitly
//
// AutLib::instant AutLib::Time::findClosestTime(const scalar t) const
// {
//     instantList timeDirs = findTimes(path());
//     label timeIndex = min(findClosestTimeIndex(timeDirs, t), 0);
//     return timeDirs[timeIndex];
// }

AutLib::label AutLib::Time::findClosestTimeIndex
(
	const instantList& timeDirs,
	const scalar t
)
{
	label nearestIndex = -1;
	scalar deltaT = GREAT;

	for (label timeI = 0; timeI < (timeDirs).size(); timeI++)
	{
		if (timeDirs[timeI].name() == "constant") continue;

		scalar diff = mag(timeDirs[timeI].value() - t);
		if (diff < deltaT)
		{
			deltaT = diff;
			nearestIndex = timeI;
		}
	}

	return nearestIndex;
}


AutLib::label AutLib::Time::startTimeIndex() const
{
	return startTimeIndex_;
}


AutLib::dimensionedScalar AutLib::Time::startTime() const
{
	return dimensionedScalar("startTime", dimTime, startTime_);
}


AutLib::dimensionedScalar AutLib::Time::endTime() const
{
	return dimensionedScalar("endTime", dimTime, endTime_);
}

bool AutLib::Time::run() const
{
	bool running = value() < (endTime_ - 0.5*deltaT_);

	if (!subCycling_)
	{
		// only execute when the condition is no longer true
		// ie, when exiting the control loop
		if (!running && timeIndex_ != startTimeIndex_)
		{
			profilingTrigger profileTriggerForfo("functionObjects_.end()");

			// Note, end() also calls an indirect start() as required
			functionObjects_.end();
		}
	}

	return running;
}


bool AutLib::Time::loop()
{
	bool running = run();

	if (running)
	{
		operator++();
	}

	return running;
}


bool AutLib::Time::end() const
{
	return value() > (endTime_ + 0.5*deltaT_);
}


void AutLib::Time::setTime(const Time& t)
{
	value() = t.value();
	dimensionedScalar::name() = t.dimensionedScalar::name();
	timeIndex_ = t.timeIndex_;
}


void AutLib::Time::setTime(const instant& inst, const label newIndex)
{
	value() = inst.value();
	dimensionedScalar::name() = inst.name();
	timeIndex_ = newIndex;

	IOdictionary timeDict
	(
		IOobject
		(
			"time",
			timeName(),
			"uniform",
			*this,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE,
			false
		)
	);

	timeDict.readIfPresent("deltaT", deltaT_);
	timeDict.readIfPresent("deltaT0", deltaT0_);
	timeDict.readIfPresent("index", timeIndex_);
}


void AutLib::Time::setTime
(
	const dimensionedScalar& newTime,
	const label newIndex
)
{
	setTime(newTime.value(), newIndex);
}


void AutLib::Time::setTime(const scalar newTime, const label newIndex)
{
	value() = newTime;
	dimensionedScalar::name() = timeName(timeToUserTime(newTime));
	timeIndex_ = newIndex;
}


void AutLib::Time::setStopAt(const stopAtControls& sa)
{
	stopAt_ = sa;
}


void AutLib::Time::setEndTime(const dimensionedScalar& endTime)
{
	setEndTime(endTime.value());
}


void AutLib::Time::setEndTime(const scalar endTime)
{
	endTime_ = endTime;
}


void AutLib::Time::setDeltaT
(
	const dimensionedScalar& deltaT,
	const bool bAdjustDeltaT
)
{
	setDeltaT(deltaT.value(), bAdjustDeltaT);
}


void AutLib::Time::setDeltaT(const scalar deltaT, const bool bAdjustDeltaT)
{
	deltaT_ = deltaT;
	deltaTchanged_ = true;

	if (bAdjustDeltaT)
	{
		adjustDeltaT();
	}
}


void AutLib::Time::setWriteControl(const writeControls& wc)
{
	writeControl_ = wc;
}


void AutLib::Time::setWriteInterval(const scalar writeInterval)
{
	writeInterval_ = writeInterval;
}


AutLib::TimeState AutLib::Time::subCycle(const label nSubCycles)
{
	subCycling_ = true;
	prevTimeState_.set(new TimeState(*this));

	setTime(*this - deltaT(), (timeIndex() - 1)*nSubCycles);
	deltaT_ /= nSubCycles;
	deltaT0_ /= nSubCycles;
	deltaTSave_ = deltaT0_;

	return prevTimeState();
}


void AutLib::Time::endSubCycle()
{
	if (subCycling_)
	{
		subCycling_ = false;
		TimeState::operator=(prevTimeState());
		prevTimeState_.clear();
	}
}

AutLib::Time& AutLib::Time::operator+=(const dimensionedScalar& deltaT)
{
	return operator+=(deltaT.value());
}


AutLib::Time& AutLib::Time::operator+=(const scalar deltaT)
{
	setDeltaT(deltaT);
	return operator++();
}


AutLib::Time& AutLib::Time::operator++()
{
	readModifiedObjects();

	if (!subCycling_)
	{
		if (timeIndex_ == startTimeIndex_)
		{
			profilingTrigger profileTriggerForfo("functionObjects_.start()");

			functionObjects_.start();
		}
		else
		{
			profilingTrigger profileTriggerForfo("functionObjects_.execute()");

			functionObjects_.execute();
		}
	}

	deltaT0_ = deltaTSave_;
	deltaTSave_ = deltaT_;

	const word oldTimeName = dimensionedScalar::name();

	setTime(value() + deltaT_, timeIndex_ + 1);

	// If the time is very close to zero reset to zero
	if (mag(value()) < 10 * SMALL*deltaT_)
	{
		setTime(0.0, timeIndex_);
	}

	// Check that new time representation differs from old one
	if (dimensionedScalar::name() == oldTimeName)
	{
		int oldPrecision = precision_;
		do
		{
			precision_++;
			setTime(value(), timeIndex());
		} while (precision_ < 100 && dimensionedScalar::name() == oldTimeName);

		WarningIn("Time::operator++()")
			<< "Increased the timePrecision from " << oldPrecision
			<< " to " << precision_
			<< " to distinguish between timeNames at time " << value()
			<< endl;
	}

	switch (writeControl_)
	{
	case wcTimeStep:
		outputTime_ = !(timeIndex_ % label(writeInterval_));
		break;

	case wcRunTime:
	case wcAdjustableRunTime:
	{
		label outputIndex =
			label(((value() - startTime_) + 0.5*deltaT_) / writeInterval_);

		if (outputIndex > outputTimeIndex_)
		{
			outputTime_ = true;
			outputTimeIndex_ = outputIndex;
		}
		else
		{
			outputTime_ = false;
		}
	}
	break;

	case wcCpuTime:
	{
		label outputIndex = label(elapsedCpuTime() / writeInterval_);
		if (outputIndex > outputTimeIndex_)
		{
			outputTime_ = true;
			outputTimeIndex_ = outputIndex;
		}
		else
		{
			outputTime_ = false;
		}
	}
	break;

	case wcClockTime:
	{
		label outputIndex = label(elapsedClockTime() / writeInterval_);
		if (outputIndex > outputTimeIndex_)
		{
			outputTime_ = true;
			outputTimeIndex_ = outputIndex;
		}
		else
		{
			outputTime_ = false;
		}
	}
	break;
	}

	// see if endTime needs adjustment to stop at the next run()/end() check
	if (!end())
	{
		if (stopAt_ == saNoWriteNow)
		{
			endTime_ = value();
		}
		else if (stopAt_ == saWriteNow)
		{
			endTime_ = value();
			outputTime_ = true;
		}
		else if (stopAt_ == saNextWrite && outputTime_ == true)
		{
			endTime_ = value();
		}
	}

	return *this;
}


AutLib::Time& AutLib::Time::operator++(int)
{
	return operator++();
}