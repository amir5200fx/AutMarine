#pragma once
#ifndef _objectRegistry_Header
#define _objectRegistry_Header

#include <regIOobject.hxx>
#include <HashTable.hxx>

namespace AutLib
{

	class Time;

	class objectRegistry
		: public regIOobject
#ifndef SWIG
		, public HashTable<regIOobject*>
#else
		, public HashTable<regIOobject*, word, string_hash>
#endif
	{
		// Private Data

		//- Master time objectRegistry
		const Time& time_;

		//- Parent objectRegistry
		const objectRegistry& parent_;

		//- Local directory path of this objectRegistry relative to time
		fileName dbDir_;

		//- Current event
		mutable label event_;


		// Private Member Functions

		//- Disallow Copy constructor
		objectRegistry(const objectRegistry&) = delete;

		//- Disallow default bitwise copy construct and assignment
		void operator=(const objectRegistry&) = delete;

	public:

		//- Declare type name for this IOobject
		static const char* typeName_() { return "objectRegistry"; }

		static const ::AutLib::word typeName;
		static AutLib::debug::debugSwitch debug;;

		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct the time objectRegistry given an initial estimate
		//  for the number of entries
		explicit objectRegistry
		(
			const Time& db,
			const label nIoObjects = 128
		);

		//- Construct a sub-registry given an IObject to describe the registry
		//  and an initial estimate for the number of entries
		explicit objectRegistry
		(
			const IOobject& io,
			const label nIoObjects = 128
		);

		//- Construct a sub-registry given an IObject to describe the registry
		//  and an initial estimate for the number of entries
		explicit objectRegistry
		(
			const IOobject& io,
			const fileName& dbDir,
			const label nIoObjects = 128
		);

		// Destructor

		virtual ~objectRegistry();


		// Member functions

		// Access

		//- Return time
		const Time& time() const;

		//- Return the parent objectRegistry
		const objectRegistry& parent() const
		{
			return parent_;
		}

		//- Local directory path of this objectRegistry
		//  relative to the time
		virtual const fileName& dbDir() const
		{
			return dbDir_;
		}

		fileName& dbDir()
		{
			return dbDir_;
		}

		//- Return mangled fileName
		virtual fileName mangleFileName(const fileName&) const;

		//- Return the list of names of the IOobjects
		wordList names() const;

		//- Return the list of names of the IOobjects of given class name
		wordList names(const word& className) const;

		//- Return the list of names of the IOobjects of given type
		template<class Type>
		wordList names() const;

		//- Lookup and return a const sub-objectRegistry
		const objectRegistry& subRegistry(const word& name) const;

		//- Lookup and return all the object of the given Type
		template<class Type>
		HashTable<const Type*> lookupClass() const;

		//- Is the named Type
		template<class Type>
		bool foundObject(const word& name) const;

		//- Lookup and return the object of the given Type
		template<class Type>
		const Type& lookupObject(const word& name) const;

		//- Return new event number.
		label getEvent() const;


		// Edit

		//- Rename
		virtual void rename(const word& newName);

		//- Add an regIOobject to registry
		virtual bool checkIn(regIOobject&) const;

		//- Remove an regIOobject from registry
		virtual bool checkOut(regIOobject&) const;


		// Reading

		//- Return true if any of the object's files have been modified
		virtual bool modified() const;

		//- Read the objects that have been modified
		void readModifiedObjects();

		//- Read object if modified
		virtual bool readIfModified();


		// Writing

		//- writeData function required by regIOobject but not used
		//  for this class, write is used instead
		virtual bool writeData(Ostream&) const
		{
			notImplemented
			(
				"void objectRegistry::writeData(Ostream&) const: "
				"use write() instead"
			);

			return false;
		}

		//- Write the objects
		virtual bool writeObject
		(
			IOstream::streamFormat fmt,
			IOstream::versionNumber ver,
			IOstream::compressionType cmp
		) const;
	};
}

#include <objectRegistryI.hxx>

#endif // !_objectRegistry_Header