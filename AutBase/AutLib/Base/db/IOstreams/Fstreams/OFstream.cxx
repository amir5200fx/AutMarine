#include <OFstream.hxx>

#include <error.hxx>
#include <OSspecific.hxx>

const ::AutLib::word AutLib::OFstream::typeName(AutLib::OFstream::typeName_());
::AutLib::debug::debugSwitch AutLib::OFstream::debug(std::string(AutLib::OFstream::typeName_()), 0, "");

AutLib::OFstreamAllocator::OFstreamAllocator
(
	const fileName& pathname,
	ios_base::openmode mode,
	IOstream::compressionType compression
)
	: ofPtr_(NULL)
{
	if (pathname.empty())
	{
		if (OFstream::debug)
		{
			Info << "OFstreamAllocator::OFstreamAllocator(const fileName&) : "
				"cannot open null file " << endl;
		}
	}

	if (compression == IOstream::COMPRESSED)
	{
		FatalErrorIn("AutLib::OFstreamAllocator::OFstreamAllocator()")
			<< "Not Implemented" << abort(FatalError);
		//// get identically named uncompressed version out of the way
		//if (isFile(pathname, false))
		//{
		//	rm(pathname);
		//}

		//ofPtr_ = new ogzstream((pathname + ".gz").c_str(), mode);
	}
	else
	{
		// get identically named compressed version out of the way
		if (isFile(pathname + ".gz", false))
		{
			rm(pathname + ".gz");
		}

		ofPtr_ = new ofstream(pathname.c_str(), mode);
	}
}


AutLib::OFstreamAllocator::~OFstreamAllocator()
{
	delete ofPtr_;
}


std::ostream& AutLib::OFstreamAllocator::stdStream()
{
	if (!ofPtr_)
	{
		FatalErrorIn("OFstreamAllocator::stdStream()")
			<< "No stream allocated." << abort(FatalError);
	}
	return *ofPtr_;
}

AutLib::OFstream::OFstream
(
	const fileName& pathname,
	ios_base::openmode mode,
	streamFormat format,
	versionNumber version,
	compressionType compression
)
	:
	OFstreamAllocator(pathname, mode, compression),
	OSstream(*ofPtr_, "OFstream.sinkFile_", format, version, compression),
	pathname_(pathname)
{
	setClosed();
	setState(ofPtr_->rdstate());

	if (!good())
	{
		if (debug)
		{
			Info << "IFstream::IFstream(const fileName&,"
				"streamFormat format=ASCII,"
				"versionNumber version=currentVersion) : "
				"could not open file for input\n"
				"in stream " << info() << AutLib::endl;
		}

		setBad();
	}
	else
	{
		setOpened();
	}

	lineNumber_ = 1;
}

AutLib::OFstream::~OFstream()
{}

void AutLib::OFstream::print(Ostream& os) const
{
	os << "    OFstream: ";
	OSstream::print(os);
}