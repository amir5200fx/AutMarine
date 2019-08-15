#include <IFstream.hxx>

#include <OSspecific.hxx>
#include <error.hxx>

const ::AutLib::word AutLib::IFstream::typeName(AutLib::IFstream::typeName_());
::AutLib::debug::debugSwitch AutLib::IFstream::debug(std::string(AutLib::IFstream::typeName_()), 0, "");

AutLib::IFstreamAllocator::IFstreamAllocator(const fileName& pathname)
	: ifPtr_(NULL)
	, compression_(IOstream::UNCOMPRESSED)
{
	if (pathname.empty())
	{
		if (IFstream::debug)
		{
			Info << "IFstreamAllocator::IFstreamAllocator(const fileName&) : "
				"cannot open null file " << endl;
		}
	}

	ifPtr_ = new ifstream(pathname.c_str());

	// If the file is compressed, decompress it before reading.
	/*if (!ifPtr_->good() && isFile(pathname + ".gz", false))
	{
		if (IFstream::debug)
		{
			Info << "IFstreamAllocator::IFstreamAllocator(const fileName&) : "
				"decompressing " << pathname + ".gz" << endl;
		}

		delete ifPtr_;

		ifPtr_ = new igzstream((pathname + ".gz").c_str());

		if (ifPtr_->good())
		{
			compression_ = IOstream::COMPRESSED;
		}
	}*/
}


AutLib::IFstreamAllocator::~IFstreamAllocator()
{
	delete ifPtr_;
}


std::istream& AutLib::IFstreamAllocator::stdStream()
{
	if (!ifPtr_)
	{
		FatalErrorIn("IFstreamAllocator::stdStream()")
			<< "No stream allocated" << abort(FatalError);
	}
	return *ifPtr_;
}

AutLib::IFstream::IFstream
(
	const fileName& pathname,
	streamFormat format,
	versionNumber version
)
	: IFstreamAllocator(pathname)
	, ISstream
	(
		*ifPtr_,
		"IFstream.sourceFile_",
		format,
		version,
		IFstreamAllocator::compression_
	)
	, pathname_(pathname)
{
	setClosed();

	setState(ifPtr_->rdstate());

	if (!good())
	{
		if (debug)
		{
			Info << "IFstream::IFstream(const fileName&,"
				"streamFormat=ASCII,"
				"versionNumber=currentVersion) : "
				"could not open file for input"
				<< endl << info() << endl;
		}

		setBad();
	}
	else
	{
		setOpened();
	}

	lineNumber_ = 1;
}

AutLib::IFstream::~IFstream()
{}

void AutLib::IFstream::print(Ostream& os) const
{
	// Print File data
	os << "IFstream: ";
	ISstream::print(os);
}

AutLib::IFstream& AutLib::IFstream::operator()() const
{
	if (!good())
	{
		// also checks .gz file
		if (isFile(pathname_, true))
		{
			check("IFstream::operator()");
			FatalIOError.exit();
		}
		else
		{
			FatalIOErrorIn("IFstream::operator()", *this)
				<< "file " << pathname_ << " does not exist"
				<< exit(FatalIOError);
		}
	}

	return const_cast<IFstream&>(*this);
}