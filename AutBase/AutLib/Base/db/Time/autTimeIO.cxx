#include <autTime.hxx>

#include <IOstreams.hxx>
#include <Pstream.hxx>
#include <profilingTrigger.hxx>
#include <PstreamReduceOps.hxx>
#include <OSspecific.hxx>
#include <uint.hxx>

void AutLib::Time::readDict()
{
	if (debug)
		Info << "Time::readDict(): reading " << controlDict_.name() << endl;

	if (!deltaTchanged_)
	{
		deltaT_ = readScalar(controlDict_.lookup("deltaT"));
	}

	if (controlDict_.found("writeControl"))
	{
		word wcName(controlDict_.lookup("writeControl"));

		if (writeControlNames_.found(wcName))
		{
			writeControl_ = writeControlNames_[wcName];
		}
		else
		{
			WarningIn("void Time::readDict()")
				<< wcName << " not found in enumeration "
				<< writeControlNames_.toc() << nl
				<< " setting writeControl to runTime" << endl;

			writeControl_ = wcTimeStep;
		}

	}

	scalar oldWriteInterval = writeInterval_;
	if (controlDict_.readIfPresent("writeInterval", writeInterval_))
	{
		if (writeControl_ == wcTimeStep && label(writeInterval_) < 1)
		{
			WarningIn("Time::readDict()")
				<< "writeInterval < 1 for writeControl timeStep.  "
				<< "Re-setting to 1."
				<< endl;

			writeInterval_ = 1;
		}
	}
	else
	{
		controlDict_.lookup("writeFrequency") >> writeInterval_;
	}

	if (oldWriteInterval != writeInterval_)
	{
		switch (writeControl_)
		{
		case wcRunTime:
		case wcAdjustableRunTime:
			// Recalculate outputTimeIndex_ to be in units of current
			// writeInterval.
			outputTimeIndex_ = label
			(
				outputTimeIndex_
				* oldWriteInterval
				/ writeInterval_
			);
			break;

		default:
			break;
		}
	}

	if (controlDict_.readIfPresent("purgeWrite", purgeWrite_))
	{
		if (purgeWrite_ < 0)
		{
			WarningIn("Time::readDict()")
				<< "invalid value for purgeWrite " << purgeWrite_
				<< ", should be >= 0, setting to 0"
				<< endl;

			purgeWrite_ = 0;
		}
	}

	if (controlDict_.found("timeFormat"))
	{
		word formatName(controlDict_.lookup("timeFormat"));

		if (formatName == "general")
		{
			format_ = general;
		}
		else if (formatName == "fixed")
		{
			format_ = fixed;
		}
		else if (formatName == "scientific")
		{
			format_ = scientific;
		}
		else
		{
			WarningIn("void Time::readDict()")
				<< "unsupported time format " << formatName
				<< endl;
		}
	}

	controlDict_.readIfPresent("timePrecision", precision_);

	// stopAt at 'endTime' or a specified value
	// if nothing is specified, the endTime is zero
	if (controlDict_.found("stopAt"))
	{
		word saName(controlDict_.lookup("stopAt"));

		if (stopAtControlNames_.found(saName))
		{
			stopAt_ = stopAtControlNames_[saName];
		}
		else
		{
			WarningIn("void Time::readDict()")
				<< saName << " not found in enumeration "
				<< stopAtControlNames_.toc() << nl
				<< "Setting to writeNow" << endl;

			stopAt_ = saWriteNow;

			// Set output time
			outputTime_ = true;
		}

		if (stopAt_ == saEndTime)
		{
			controlDict_.lookup("endTime") >> endTime_;
		}
		else
		{
			endTime_ = GREAT;
		}
	}
	else if (!controlDict_.readIfPresent("endTime", endTime_))
	{
		endTime_ = 0;
	}

	dimensionedScalar::name() = timeName(value());

	if (controlDict_.found("writeVersion"))
	{
		writeVersion_ = IOstream::versionNumber
		(
			controlDict_.lookup("writeVersion")
		);
	}

	if (controlDict_.found("writeFormat"))
	{
		writeFormat_ = IOstream::formatEnum
		(
			controlDict_.lookup("writeFormat")
		);
	}

	if (controlDict_.found("writePrecision"))
	{
		IOstream::defaultPrecision
		(
			readUint(controlDict_.lookup("writePrecision"))
		);

		Sout.precision(IOstream::defaultPrecision());
		Serr.precision(IOstream::defaultPrecision());

		Pout.precision(IOstream::defaultPrecision());
		Perr.precision(IOstream::defaultPrecision());
	}

	if (controlDict_.found("writeCompression"))
	{
		writeCompression_ = IOstream::compressionEnum
		(
			controlDict_.lookup("writeCompression")
		);
	}

	controlDict_.readIfPresent("graphFormat", graphFormat_);
	controlDict_.readIfPresent("runTimeModifiable", runTimeModifiable_);
}


bool AutLib::Time::read()
{
	if (controlDict_.regIOobject::read())
	{
		readDict();

		return true;
	}
	else
	{
		return false;
	}
}


void AutLib::Time::readModifiedObjects()
{
	if (runTimeModifiable_)
	{
		// For parallel runs check if any object's file has been modified
		// and only call readIfModified on each object if this is the case
		// to avoid unnecessary reductions in readIfModified for each object

		bool anyModified = true;

		if (Pstream::parRun())
		{
			anyModified = controlDict_.modified()
				|| objectRegistry::modified();

			bool anyModifiedOnThisProc = anyModified;
			reduce(anyModified, andOp<bool>());

			if (anyModifiedOnThisProc && !anyModified)
			{
				WarningIn("Time::readModifiedObjects()")
					<< "Delaying reading objects due to inconsistent "
					"file time-stamps between processors"
					<< endl;
			}
		}

		if (anyModified)
		{
			if (controlDict_.readIfModified())
			{
				readDict();
				functionObjects_.read();
			}

			objectRegistry::readModifiedObjects();
		}
	}
}


bool AutLib::Time::writeObject
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp
) const
{
	AutLib::profilingTrigger profileTriggerForgetCalled("AutLib::Time::writeObject");

	if (outputTime())
	{
		AutLib::profilingTrigger profileTriggerForactualOutput("AutLib::Time::writeObject - outputTime");

		IOdictionary timeDict
		(
			IOobject
			(
				"time",
				timeName(),
				"uniform",
				*this,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			)
		);

		timeDict.add("index", timeIndex_);
		timeDict.add("deltaT", deltaT_);
		timeDict.add("deltaT0", deltaT0_);

		timeDict.regIOobject::writeObject(fmt, ver, cmp);
		bool writeOK = objectRegistry::writeObject(fmt, ver, cmp);

		if (writeOK && purgeWrite_)
		{
			previousOutputTimes_.push(timeName());

			while (previousOutputTimes_.size() > purgeWrite_)
			{
				rmDir(objectRegistry::path(previousOutputTimes_.pop()));
			}
		}

		return writeOK;
	}
	else
	{
		return false;
	}
}


bool AutLib::Time::writeNow()
{
	outputTime_ = true;
	return write();
}


bool AutLib::Time::writeAndEnd()
{
	stopAt_ = saWriteNow;
	endTime_ = value();

	return writeNow();
}