#include <regIOobject.hxx>

#include <objectRegistry.hxx>
#include <error.hxx>

#include <objectRegistryTemplates.cxx>

const ::AutLib::word AutLib::regIOobject::typeName(AutLib::regIOobject::typeName_());
::AutLib::debug::debugSwitch AutLib::regIOobject::debug(std::string(AutLib::regIOobject::typeName_()), 0, "");;

const AutLib::debug::optimisationSwitch
AutLib::regIOobject::fileModificationSkew
(
	"fileModificationSkew",
	30
);

// Construct from IOobject
AutLib::regIOobject::regIOobject(const IOobject& io, const bool isTime)
	: IOobject(io)
	, registered_(false)
	, ownedByRegistry_(false)
	, lastModified_(0)
	, eventNo_                // Do not get event for top level Time database
	(
		isTime
		? 0
		: db().getEvent()
	)
	, isPtr_(NULL)
{
	// Register with objectRegistry if requested
	if (registerObject())
	{
		checkIn();
	}
}


// Construct as copy
AutLib::regIOobject::regIOobject(const regIOobject& rio)
	: IOobject(rio)
	, registered_(false)
	, ownedByRegistry_(false)
	, lastModified_(rio.lastModified_)
	, eventNo_(db().getEvent())
	, isPtr_(NULL)
{
	// Do not register copy with objectRegistry
}


// Construct as copy, and transfering objectRegistry registration to copy
// if registerCopy is true
AutLib::regIOobject::regIOobject(const regIOobject& rio, bool registerCopy)
	: IOobject(rio)
	, registered_(false)
	, ownedByRegistry_(false)
	, lastModified_(rio.lastModified_)
	, eventNo_(db().getEvent())
	, isPtr_(NULL)
{
	if (registerCopy && rio.registered_)
	{
		const_cast<regIOobject&>(rio).checkOut();
		checkIn();
	}
}

// Delete read stream, checkout from objectRegistry and destroy
AutLib::regIOobject::~regIOobject()
{
	if (objectRegistry::debug)
	{
		Info << "Destroying regIOobject called " << name()
			<< " of type " << type()
			<< " in directory " << path()
			<< endl;
	}

	if (isPtr_)
	{
		delete isPtr_;
		isPtr_ = NULL;
	}

	// Check out of objectRegistry if not owned by the registry
	if (!ownedByRegistry_)
	{
		checkOut();
	}
}

bool AutLib::regIOobject::checkIn()
{
	FatalErrorIn("Not supposed to be run: bool AutLib::regIOobject::checkIn()") << abort(FatalError);
	//if (!registered_)
	//{
	//	// multiple checkin of same object is disallowed - this would mess up
	//	// any mapping
	//	registered_ = db().checkIn(*this);

	//	// check-in on defaultRegion is allowed to fail, since subsetted meshes
	//	// are created with the same name as their originating mesh
	//	if (!registered_ && debug && name() != polyMesh::defaultRegion)
	//	{
	//		if (debug == 2)
	//		{
	//			// for ease of finding where attempted duplicate check-in
	//			// originated
	//			FatalErrorIn("regIOobject::checkIn()")
	//				<< "failed to register object " << objectPath()
	//				<< " the name already exists in the objectRegistry"
	//				<< abort(FatalError);
	//		}
	//		else
	//		{
	//			WarningIn("regIOobject::checkIn()")
	//				<< "failed to register object " << objectPath()
	//				<< " the name already exists in the objectRegistry"
	//				<< endl;
	//		}
	//	}
	//}

	return registered_;
}


bool AutLib::regIOobject::checkOut()
{
	if (registered_)
	{
		registered_ = false;
		return db().checkOut(*this);
	}

	return false;
}


bool AutLib::regIOobject::upToDate(const word& a) const
{
	if (db().lookupObject<regIOobject>(a).eventNo() >= eventNo_)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool AutLib::regIOobject::upToDate(const word& a, const word& b) const
{
	if
		(
			db().lookupObject<regIOobject>(a).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(b).eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool AutLib::regIOobject::upToDate
(
	const word& a,
	const word& b,
	const word& c
) const
{
	if
		(
			db().lookupObject<regIOobject>(a).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(b).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(c).eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool AutLib::regIOobject::upToDate
(
	const word& a,
	const word& b,
	const word& c,
	const word& d
) const
{
	if
		(
			db().lookupObject<regIOobject>(a).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(b).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(c).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(d).eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//- Flag me as up to date
void AutLib::regIOobject::setUpToDate()
{
	eventNo_ = db().getEvent();
}


// Rename object and re-register with objectRegistry under new name
void AutLib::regIOobject::rename(const word& newName)
{
	// Check out of objectRegistry
	checkOut();

	IOobject::rename(newName);

	if (registerObject())
	{
		// Re-register object with objectRegistry
		checkIn();
	}
}


// Assign to IOobject
void AutLib::regIOobject::operator=(const IOobject& io)
{
	if (isPtr_)
	{
		delete isPtr_;
		isPtr_ = NULL;
	}

	// Check out of objectRegistry
	checkOut();

	IOobject::operator=(io);

	if (registerObject())
	{
		// Re-register object with objectRegistry
		checkIn();
	}
}