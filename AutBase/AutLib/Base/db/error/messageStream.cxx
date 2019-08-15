#include <messageStream.hxx>

#include <error.hxx>
#include <dictionary.hxx>
#include <Pstream.hxx>
#include <IOstreams.hxx>
#include <OFstream.hxx>
#include <ITstream.hxx>

AutLib::debug::debugSwitch
AutLib::messageStream::level
(
	"level",
	2
);

AutLib::messageStream::messageStream
(
	const string& title,
	errorSeverity sev,
	const int maxErrors
)
	: title_(title)
	, severity_(sev)
	, maxErrors_(maxErrors)
	, errorCount_(0)
{}


AutLib::messageStream::messageStream(const dictionary& dict)
	: title_(dict.lookup("title"))
	, severity_(FATAL)
	, maxErrors_(0)
	, errorCount_(0)
{}


AutLib::OSstream& AutLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber
	)
{
	OSstream& os = operator OSstream&();

	os << endl
		<< "    From function " << functionName << endl
		<< "    in file " << sourceFileName
		<< " at line " << sourceFileLineNumber << endl
		<< "    ";

	return os;
}


AutLib::OSstream& AutLib::messageStream::operator()
(
	const string& functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber
	)
{
	return operator()
		(
			functionName.c_str(),
			sourceFileName,
			sourceFileLineNumber
			);
}


AutLib::OSstream& AutLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const string& ioFileName,
	const label ioStartLineNumber,
	const label ioEndLineNumber
	)
{
	OSstream& os = operator OSstream&();

	os << endl
		<< "    From function " << functionName << endl
		<< "    in file " << sourceFileName
		<< " at line " << sourceFileLineNumber << endl
		<< "    Reading " << ioFileName;

	if (ioStartLineNumber >= 0 && ioEndLineNumber >= 0)
	{
		os << " from line " << ioStartLineNumber
			<< " to line " << ioEndLineNumber;
	}
	else if (ioStartLineNumber >= 0)
	{
		os << " at line " << ioStartLineNumber;
	}

	os << endl << "    ";

	return os;
}


AutLib::OSstream& AutLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const IOstream& ioStream
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			ioStream.name(),
			ioStream.lineNumber(),
			-1
			);
}


AutLib::OSstream& AutLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const dictionary& dict
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			dict.name(),
			dict.startLineNumber(),
			dict.endLineNumber()
			);
}


namespace AutLib
{
	messageStream::operator OSstream&()
	{
		if (level)
		{
			bool collect = (severity_ == INFO || severity_ == WARNING);

			// Report the error
			if (!Pstream::master() && collect)
			{
				return Snull;
			}
			else
			{
				if (title().size())
				{
					if (Pstream::parRun() && !collect)
					{
						Pout << title().c_str();
					}
					else
					{
						Sout << title().c_str();
					}
				}

				if (maxErrors_)
				{
					errorCount_++;

					if (errorCount_ >= maxErrors_)
					{
						FatalErrorIn("messageStream::operator OSstream&()")
							<< "Too many errors"
							<< abort(FatalError);
					}
				}

				if (Pstream::parRun() && !collect)
				{
					return Pout;
				}
				else
				{
					return Sout;
				}
			}
		}

		return Snull;
	}
}

AutLib::messageStream AutLib::SeriousError
(
	"--> FOAM Serious Error : ",
	messageStream::SERIOUS,
	100
);

AutLib::messageStream AutLib::Warning
(
	"--> FOAM Warning : ",
	messageStream::WARNING
);

AutLib::messageStream AutLib::Info("", messageStream::INFO);