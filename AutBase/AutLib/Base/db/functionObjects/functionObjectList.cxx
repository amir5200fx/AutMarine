#include <functionObjectList.hxx>

#include <autTime.hxx>
#include <profilingTrigger.hxx>

AutLib::functionObject* AutLib::functionObjectList::remove(const word& key, label& oldIndex)
{
	functionObject* ptr = 0;

	// Find index of existing functionObject
	HashTable<label>::iterator fnd = indices_.find(key);

	if (fnd != indices_.end())
	{
		oldIndex = fnd();

		// retrieve the pointer and remove it from the old list
		ptr = this->set(oldIndex, 0).ptr();
		indices_.erase(fnd);
	}
	else
	{
		oldIndex = -1;
	}

	return ptr;
}

AutLib::functionObjectList::functionObjectList
(
	const Time& t,
	const bool execution
)
	: PtrList<functionObject>()
	, digests_()
	, indices_()
	, time_(t)
	, parentDict_(t.controlDict())
	, execution_(execution)
	, updated_(false)
{}


AutLib::functionObjectList::functionObjectList
(
	const Time& t,
	const dictionary& parentDict,
	const bool execution
)
	: PtrList<functionObject>()
	, digests_()
	, indices_()
	, time_(t)
	, parentDict_(parentDict)
	, execution_(execution)
	, updated_(false)
{}

AutLib::functionObjectList::~functionObjectList()
{}

void AutLib::functionObjectList::clear()
{
	PtrList<functionObject>::clear();
	digests_.clear();
	indices_.clear();
	updated_ = false;
}


void AutLib::functionObjectList::on()
{
	execution_ = true;
}


void AutLib::functionObjectList::off()
{
	// for safety, also force a read() when execution is turned back on
	updated_ = execution_ = false;
}


bool AutLib::functionObjectList::status() const
{
	return execution_;
}


bool AutLib::functionObjectList::start()
{
	return read();
}


bool AutLib::functionObjectList::execute()
{
	bool ok = true;

	if (execution_)
	{
		if (!updated_)
		{
			read();
		}

		for (PtrList<functionObject>::iterator iter = (static_cast<PtrList<functionObject>&>(*this)).begin(); iter != (static_cast<PtrList<functionObject>&>(*this)).end(); ++iter)
		{
			AutLib::profilingTrigger profileTriggerForfo("FO::" + (*iter).name() + "::execute");

			ok = iter().execute() && ok;
		}
	}

	return ok;
}


bool AutLib::functionObjectList::end()
{
	bool ok = true;

	if (execution_)
	{
		if (!updated_)
		{
			read();
		}

		for (PtrList<functionObject>::iterator iter = (static_cast<PtrList<functionObject>&>(*this)).begin(); iter != (static_cast<PtrList<functionObject>&>(*this)).end(); ++iter)
		{
			AutLib::profilingTrigger profileTriggerForfo("FO::" + (*iter).name() + "::end");

			ok = iter().end() && ok;
		}
	}

	return ok;
}


bool AutLib::functionObjectList::read()
{
	bool ok = true;
	updated_ = execution_;

	AutLib::profilingTrigger profileTriggerForfo("functionObjectList::read");

	// avoid reading/initializing if execution is off
	if (!execution_)
	{
		return ok;
	}

	// Update existing and add new functionObjects
	const entry* entryPtr = parentDict_.lookupEntryPtr
	(
		"functions",
		false,
		false
	);

	if (entryPtr)
	{
		PtrList<functionObject> newPtrs;
		List<SHA1Digest> newDigs;
		HashTable<label> newIndices;

		label nFunc = 0;

		if (entryPtr->isDict())
		{
			// a dictionary of functionObjects
			const dictionary& functionDicts = entryPtr->dict();

			newPtrs.setSize(functionDicts.size());
			newDigs.setSize(functionDicts.size());

			for (dictionary::const_iterator iter = (functionDicts).begin(); iter != (functionDicts).end(); ++iter)
			{
				// safety:
				if (!iter().isDict())
				{
					continue;
				}
				const word& key = iter().keyword();
				const dictionary& dict = iter().dict();

				newDigs[nFunc] = dict.digest();

				label oldIndex;
				functionObject* objPtr = remove(key, oldIndex);
				if (objPtr)
				{
					// an existing functionObject, and dictionary changed
					if (newDigs[nFunc] != digests_[oldIndex])
					{
						AutLib::profilingTrigger profileTriggerForfo("FO::" + objPtr->name() + "::read");

						ok = objPtr->read(dict) && ok;
					}
				}
				else
				{
					// new functionObject
					objPtr = functionObject::New(key, time_, dict).ptr();

					AutLib::profilingTrigger profileTriggerForfo("FO::" + objPtr->name() + "::start");

					ok = objPtr->start() && ok;
				}

				newPtrs.set(nFunc, objPtr);
				newIndices.insert(key, nFunc);
				nFunc++;
			}
		}
		else
		{
			// a list of functionObjects
			PtrList<entry> functionDicts(entryPtr->stream());

			newPtrs.setSize(functionDicts.size());
			newDigs.setSize(functionDicts.size());

			for (PtrList<entry>::iterator iter = (functionDicts).begin(); iter != (functionDicts).end(); ++iter)
			{
				// safety:
				if (!iter().isDict())
				{
					continue;
				}
				const word& key = iter().keyword();
				const dictionary& dict = iter().dict();

				newDigs[nFunc] = dict.digest();

				label oldIndex;
				functionObject* objPtr = remove(key, oldIndex);
				if (objPtr)
				{
					// an existing functionObject, and dictionary changed
					if (newDigs[nFunc] != digests_[oldIndex])
					{
						ok = objPtr->read(dict) && ok;
					}
				}
				else
				{
					// new functionObject
					objPtr = functionObject::New(key, time_, dict).ptr();
					ok = objPtr->start() && ok;
				}

				newPtrs.set(nFunc, objPtr);
				newIndices.insert(key, nFunc);
				nFunc++;
			}
		}

		// safety:
		newPtrs.setSize(nFunc);
		newDigs.setSize(nFunc);

		// updating the PtrList of functionObjects also deletes any existing,
		// but unused functionObjects
		PtrList<functionObject>::transfer(newPtrs);
		digests_.transfer(newDigs);
		indices_.transfer(newIndices);
	}
	else
	{
		PtrList<functionObject>::clear();
		digests_.clear();
		indices_.clear();
	}

	return ok;
}