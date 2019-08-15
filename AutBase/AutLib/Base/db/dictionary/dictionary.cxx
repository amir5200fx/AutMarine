#include <dictionary.hxx>

#include <regExp.hxx>
#include <wordList.hxx>
#include <OSHA1stream.hxx>
#include <primitiveEntry.hxx>
#include <dictionaryEntry.hxx>

const ::AutLib::word AutLib::dictionary::typeName(AutLib::dictionary::typeName_());
::AutLib::debug::debugSwitch AutLib::dictionary::debug(std::string(AutLib::dictionary::typeName_()), 0, "");;

const AutLib::dictionary AutLib::dictionary::null;

bool AutLib::dictionary::findInPatterns
(
	const bool patternMatch,
	const word& Keyword,
	DLList<entry*>::const_iterator& wcLink,
	DLList<autoPtr<regExp> >::const_iterator& reLink
) const
{
	if (patternEntries_.size())
	{
		while (wcLink != patternEntries_.end())
		{
			if
				(
					patternMatch
					? reLink()->match(Keyword)
					: wcLink()->keyword() == Keyword
					)
			{
				return true;
			}

			++reLink;
			++wcLink;
		}
	}

	return false;
}


bool AutLib::dictionary::findInPatterns
(
	const bool patternMatch,
	const word& Keyword,
	DLList<entry*>::iterator& wcLink,
	DLList<autoPtr<regExp> >::iterator& reLink
)
{
	if (patternEntries_.size())
	{
		while (wcLink != patternEntries_.end())
		{
			if
				(
					patternMatch
					? reLink()->match(Keyword)
					: wcLink()->keyword() == Keyword
					)
			{
				return true;
			}

			++reLink;
			++wcLink;
		}
	}

	return false;
}

AutLib::dictionary::dictionary()
	: parent_(dictionary::null)
{}


AutLib::dictionary::dictionary(const fileName& name)
	: dictionaryName(name)
	, parent_(dictionary::null)
{}


AutLib::dictionary::dictionary
(
	const dictionary& parentDict,
	const dictionary& dict
)
	: dictionaryName(dict.name())
	, IDLList<entry>(dict, *this)
	, parent_(parentDict)
{
	for (IDLList<entry>::iterator iter = (*this).begin(); iter != (*this).end(); ++iter)
	{
		hashedEntries_.insert(iter().keyword(), &iter());

		if (iter().keyword().isPattern())
		{
			patternEntries_.insert(&iter());
			patternRegexps_.insert
			(
				autoPtr<regExp>(new regExp(iter().keyword()))
			);
		}
	}
}


AutLib::dictionary::dictionary
(
	const dictionary& dict
)
	: dictionaryName(dict.name())
	, IDLList<entry>(dict, *this)
	, parent_(dictionary::null)
{
	for (IDLList<entry>::iterator iter = (*this).begin(); iter != (*this).end(); ++iter)
	{
		hashedEntries_.insert(iter().keyword(), &iter());

		if (iter().keyword().isPattern())
		{
			patternEntries_.insert(&iter());
			patternRegexps_.insert
			(
				autoPtr<regExp>(new regExp(iter().keyword()))
			);
		}
	}
}


AutLib::dictionary::dictionary
(
	const dictionary* dictPtr
)
	: parent_(dictionary::null)
{
	if (dictPtr)
	{
		operator=(*dictPtr);
	}
}


AutLib::dictionary::dictionary
(
	const dictionary& parentDict,
	const Xfer<dictionary>& dict
)
	: parent_(parentDict)
{
	transfer(dict());
	name() = parentDict.name() + "::" + name();
}


AutLib::dictionary::dictionary
(
	const Xfer<dictionary>& dict
)
	: parent_(dictionary::null)
{
	transfer(dict());
}


AutLib::autoPtr<AutLib::dictionary> AutLib::dictionary::clone() const
{
	return autoPtr<dictionary>(new dictionary(*this));
}

AutLib::dictionary::~dictionary()
{
	// cerr<< "~dictionary() " << name() << " " << long(this) << std::endl;
}

AutLib::label AutLib::dictionary::startLineNumber() const
{
	if (size())
	{
		return first()->startLineNumber();
	}
	else
	{
		return -1;
	}
}


AutLib::label AutLib::dictionary::endLineNumber() const
{
	if (size())
	{
		return last()->endLineNumber();
	}
	else
	{
		return -1;
	}
}


AutLib::SHA1Digest AutLib::dictionary::digest() const
{
	OSHA1stream os;

	// process entries
	for (IDLList<entry>::const_iterator iter = (*this).begin(); iter != (*this).end(); ++iter)
	{
		os << *iter;
	}

	return os.digest();
}


bool AutLib::dictionary::found(const word& keyword, bool recursive) const
{
	if (hashedEntries_.found(keyword))
	{
		return true;
	}
	else
	{
		if (patternEntries_.size())
		{
			DLList<entry*>::const_iterator wcLink =
				patternEntries_.begin();
			DLList<autoPtr<regExp> >::const_iterator reLink =
				patternRegexps_.begin();

			// Find in patterns using regular expressions only
			if (findInPatterns(true, keyword, wcLink, reLink))
			{
				return true;
			}
		}

		if (recursive && &parent_ != &dictionary::null)
		{
			return parent_.found(keyword, recursive);
		}
		else
		{
			return false;
		}
	}
}


const AutLib::entry* AutLib::dictionary::lookupEntryPtr
(
	const word& keyword,
	bool recursive,
	bool patternMatch
) const
{
	HashTable<entry*>::const_iterator iter = hashedEntries_.find(keyword);

	if (iter == hashedEntries_.end())
	{
		if (patternMatch && patternEntries_.size())
		{
			DLList<entry*>::const_iterator wcLink =
				patternEntries_.begin();
			DLList<autoPtr<regExp> >::const_iterator reLink =
				patternRegexps_.begin();

			// Find in patterns using regular expressions only
			if (findInPatterns(patternMatch, keyword, wcLink, reLink))
			{
				return wcLink();
			}
		}

		if (recursive && &parent_ != &dictionary::null)
		{
			return parent_.lookupEntryPtr(keyword, recursive, patternMatch);
		}
		else
		{
			return NULL;
		}
	}

	return iter();
}


AutLib::entry* AutLib::dictionary::lookupEntryPtr
(
	const word& keyword,
	bool recursive,
	bool patternMatch
)
{
	HashTable<entry*>::iterator iter = hashedEntries_.find(keyword);

	if (iter == hashedEntries_.end())
	{
		if (patternMatch && patternEntries_.size())
		{
			DLList<entry*>::iterator wcLink =
				patternEntries_.begin();
			DLList<autoPtr<regExp> >::iterator reLink =
				patternRegexps_.begin();

			// Find in patterns using regular expressions only
			if (findInPatterns(patternMatch, keyword, wcLink, reLink))
			{
				return wcLink();
			}
		}

		if (recursive && &parent_ != &dictionary::null)
		{
			return const_cast<dictionary&>(parent_).lookupEntryPtr
			(
				keyword,
				recursive,
				patternMatch
			);
		}
		else
		{
			return NULL;
		}
	}

	return iter();
}


const AutLib::entry& AutLib::dictionary::lookupEntry
(
	const word& keyword,
	bool recursive,
	bool patternMatch
) const
{
	const entry* entryPtr = lookupEntryPtr(keyword, recursive, patternMatch);

	if (entryPtr == NULL)
	{
		FatalIOErrorIn
		(
			"dictionary::lookupEntry(const word&, bool, bool) const",
			*this
		) << "keyword " << keyword << " is undefined in dictionary "
			<< name()
			<< exit(FatalIOError);
	}

	return *entryPtr;
}


AutLib::ITstream& AutLib::dictionary::lookup
(
	const word& keyword,
	bool recursive,
	bool patternMatch
) const
{
	return lookupEntry(keyword, recursive, patternMatch).stream();
}


bool AutLib::dictionary::isDict(const word& keyword) const
{
	// Find non-recursive with patterns
	const entry* entryPtr = lookupEntryPtr(keyword, false, true);

	if (entryPtr)
	{
		return entryPtr->isDict();
	}
	else
	{
		return false;
	}
}


const AutLib::dictionary* AutLib::dictionary::subDictPtr(const word& keyword) const
{
	const entry* entryPtr = lookupEntryPtr(keyword, false, true);

	if (entryPtr)
	{
		return &entryPtr->dict();
	}
	else
	{
		return NULL;
	}
}


const AutLib::dictionary& AutLib::dictionary::subDict(const word& keyword) const
{
	const entry* entryPtr = lookupEntryPtr(keyword, false, true);

	if (entryPtr == NULL)
	{
		FatalIOErrorIn
		(
			"dictionary::subDict(const word& keyword) const",
			*this
		) << "keyword " << keyword << " is undefined in dictionary "
			<< name()
			<< exit(FatalIOError);
	}
	return entryPtr->dict();
}


AutLib::dictionary& AutLib::dictionary::subDict(const word& keyword)
{
	entry* entryPtr = lookupEntryPtr(keyword, false, true);

	if (entryPtr == NULL)
	{
		FatalIOErrorIn
		(
			"dictionary::subDict(const word& keyword)",
			*this
		) << "keyword " << keyword << " is undefined in dictionary "
			<< name()
			<< exit(FatalIOError);
	}
	return entryPtr->dict();
}


AutLib::dictionary AutLib::dictionary::subOrEmptyDict
(
	const word& keyword
) const
{
	const entry* entryPtr = lookupEntryPtr(keyword, false, true);

	if (entryPtr == NULL)
	{
		return dictionary(*this, dictionary(name() + "::" + keyword));
	}
	else
	{
		return entryPtr->dict();
	}
}


AutLib::wordList AutLib::dictionary::toc() const
{
	wordList keys(size());

	label nKeys = 0;
	for (IDLList<entry>::const_iterator iter = (*this).begin(); iter != (*this).end(); ++iter)
	{
		keys[nKeys++] = iter().keyword();
	}

	return keys;
}


AutLib::List<AutLib::keyType> AutLib::dictionary::keys(bool patterns) const
{
	List<keyType> keys(size());

	label nKeys = 0;
	for (IDLList<entry>::const_iterator iter = (*this).begin(); iter != (*this).end(); ++iter)
	{
		if (iter().keyword().isPattern() ? patterns : !patterns)
		{
			keys[nKeys++] = iter().keyword();
		}
	}
	keys.setSize(nKeys);

	return keys;
}


bool AutLib::dictionary::add(entry* entryPtr, bool mergeEntry)
{
	HashTable<entry*>::iterator iter = hashedEntries_.find
	(
		entryPtr->keyword()
	);

	if (mergeEntry && iter != hashedEntries_.end())
	{
		// merge dictionary with dictionary
		if (iter()->isDict() && entryPtr->isDict())
		{
			iter()->dict().merge(entryPtr->dict());
			delete entryPtr;

			return true;
		}
		else
		{
			// replace existing dictionary with entry or vice versa
			IDLList<entry>::replace(iter(), entryPtr);
			delete iter();
			hashedEntries_.erase(iter);

			if (hashedEntries_.insert(entryPtr->keyword(), entryPtr))
			{
				entryPtr->name() = name() + "::" + entryPtr->keyword();

				if (entryPtr->keyword().isPattern())
				{
					patternEntries_.insert(entryPtr);
					patternRegexps_.insert
					(
						autoPtr<regExp>(new regExp(entryPtr->keyword()))
					);
				}

				return true;
			}
			else
			{
				IOWarningIn("dictionary::add(entry*, bool)", (*this))
					<< "problem replacing entry " << entryPtr->keyword()
					<< " in dictionary " << name() << endl;

				IDLList<entry>::remove(entryPtr);
				delete entryPtr;
				return false;
			}
		}
	}

	if (hashedEntries_.insert(entryPtr->keyword(), entryPtr))
	{
		entryPtr->name() = name() + "::" + entryPtr->keyword();
		IDLList<entry>::append(entryPtr);

		if (entryPtr->keyword().isPattern())
		{
			patternEntries_.insert(entryPtr);
			patternRegexps_.insert
			(
				autoPtr<regExp>(new regExp(entryPtr->keyword()))
			);
		}

		return true;
	}
	else
	{
		IOWarningIn("dictionary::add(entry*, bool)", (*this))
			<< "attempt to add entry " << entryPtr->keyword()
			<< " which already exists in dictionary " << name()
			<< endl;

		delete entryPtr;
		return false;
	}
}


void AutLib::dictionary::add(const entry& e, bool mergeEntry)
{
	add(e.clone(*this).ptr(), mergeEntry);
}


void AutLib::dictionary::add(const keyType& k, const word& w, bool overwrite)
{
	add(new primitiveEntry(k, token(w)), overwrite);
}


void AutLib::dictionary::add
(
	const keyType& k,
	const AutLib::string& s,
	bool overwrite
)
{
	add(new primitiveEntry(k, token(s)), overwrite);
}


void AutLib::dictionary::add(const keyType& k, const label l, bool overwrite)
{
	add(new primitiveEntry(k, token(l)), overwrite);
}


void AutLib::dictionary::add(const keyType& k, const scalar s, bool overwrite)
{
	add(new primitiveEntry(k, token(s)), overwrite);
}


void AutLib::dictionary::add
(
	const keyType& k,
	const dictionary& d,
	bool mergeEntry
)
{
	add(new dictionaryEntry(k, *this, d), mergeEntry);
}


void AutLib::dictionary::set(entry* entryPtr)
{
	entry* existingPtr = lookupEntryPtr(entryPtr->keyword(), false, true);

	// clear dictionary so merge acts like overwrite
	if (existingPtr && existingPtr->isDict())
	{
		existingPtr->dict().clear();
	}
	add(entryPtr, true);
}


void AutLib::dictionary::set(const entry& e)
{
	set(e.clone(*this).ptr());
}


void AutLib::dictionary::set(const keyType& k, const dictionary& d)
{
	set(new dictionaryEntry(k, *this, d));
}


bool AutLib::dictionary::remove(const word& Keyword)
{
	HashTable<entry*>::iterator iter = hashedEntries_.find(Keyword);

	if (iter != hashedEntries_.end())
	{
		// Delete from patterns first
		DLList<entry*>::iterator wcLink =
			patternEntries_.begin();
		DLList<autoPtr<regExp> >::iterator reLink =
			patternRegexps_.begin();

		// Find in pattern using exact match only
		if (findInPatterns(false, Keyword, wcLink, reLink))
		{
			patternEntries_.remove(wcLink);
			patternRegexps_.remove(reLink);
		}

		IDLList<entry>::remove(iter());
		delete iter();
		hashedEntries_.erase(iter);

		return true;
	}
	else
	{
		return false;
	}
}


bool AutLib::dictionary::changeKeyword
(
	const keyType& oldKeyword,
	const keyType& newKeyword,
	bool forceOverwrite
)
{
	// no change
	if (oldKeyword == newKeyword)
	{
		return false;
	}

	HashTable<entry*>::iterator iter = hashedEntries_.find(oldKeyword);

	// oldKeyword not found - do nothing
	if (iter == hashedEntries_.end())
	{
		return false;
	}

	if (iter()->keyword().isPattern())
	{
		FatalErrorIn
		(
			"dictionary::changeKeyword(const word&, const word&, bool)"
		) << "Old keyword " << oldKeyword
			<< " is a pattern."
			<< "Pattern replacement not yet implemented."
			<< exit(FatalError);
	}


	HashTable<entry*>::iterator iter2 = hashedEntries_.find(newKeyword);

	// newKeyword already exists
	if (iter2 != hashedEntries_.end())
	{
		if (forceOverwrite)
		{
			if (iter2()->keyword().isPattern())
			{
				// Delete from patterns first
				DLList<entry*>::iterator wcLink =
					patternEntries_.begin();
				DLList<autoPtr<regExp> >::iterator reLink =
					patternRegexps_.begin();

				// Find in patterns using exact match only
				if (findInPatterns(false, iter2()->keyword(), wcLink, reLink))
				{
					patternEntries_.remove(wcLink);
					patternRegexps_.remove(reLink);
				}
			}

			IDLList<entry>::replace(iter2(), iter());
			delete iter2();
			hashedEntries_.erase(iter2);

		}
		else
		{
			WarningIn
			(
				"dictionary::changeKeyword(const word&, const word&, bool)"
			) << "cannot rename keyword " << oldKeyword
				<< " to existing keyword " << newKeyword
				<< " in dictionary " << name() << endl;
			return false;
		}
	}

	// change name and HashTable, but leave DL-List untouched
	iter()->keyword() = newKeyword;
	iter()->name() = name() + "::" + newKeyword;
	hashedEntries_.erase(oldKeyword);
	hashedEntries_.insert(newKeyword, iter());

	if (newKeyword.isPattern())
	{
		patternEntries_.insert(iter());
		patternRegexps_.insert
		(
			autoPtr<regExp>(new regExp(newKeyword))
		);
	}

	return true;
}


bool AutLib::dictionary::merge(const dictionary& dict)
{
	// Check for assignment to self
	if (this == &dict)
	{
		FatalErrorIn("dictionary::merge(const dictionary&)")
			<< "attempted merge to self for dictionary " << name()
			<< abort(FatalError);
	}

	bool changed = false;

	for (IDLList<entry>::const_iterator iter = (dict).begin(); iter != (dict).end(); ++iter)
	{
		HashTable<entry*>::iterator fnd = hashedEntries_.find(iter().keyword());

		if (fnd != hashedEntries_.end())
		{
			// Recursively merge sub-dictionaries
			// TODO: merge without copying
			if (fnd()->isDict() && iter().isDict())
			{
				if (fnd()->dict().merge(iter().dict()))
				{
					changed = true;
				}
			}
			else
			{
				add(iter().clone(*this).ptr(), true);
				changed = true;
			}
		}
		else
		{
			// not found - just add
			add(iter().clone(*this).ptr());
			changed = true;
		}
	}

	return changed;
}


void AutLib::dictionary::clear()
{
	IDLList<entry>::clear();
	hashedEntries_.clear();
	patternEntries_.clear();
	patternRegexps_.clear();
}


void AutLib::dictionary::transfer(dictionary& dict)
{
	// changing parents probably doesn't make much sense,
	// but what about the names?
	name() = dict.name();

	IDLList<entry>::transfer(dict);
	hashedEntries_.transfer(dict.hashedEntries_);
	patternEntries_.transfer(dict.patternEntries_);
	patternRegexps_.transfer(dict.patternRegexps_);
}


AutLib::Xfer<AutLib::dictionary> AutLib::dictionary::xfer()
{
	return xferMove(*this);
}

AutLib::ITstream& AutLib::dictionary::operator[](const word& keyword) const
{
	return lookup(keyword);
}


void AutLib::dictionary::operator=(const dictionary& rhs)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorIn("dictionary::operator=(const dictionary&)")
			<< "attempted assignment to self for dictionary " << name()
			<< abort(FatalError);
	}

	name() = rhs.name();
	clear();

	// Create clones of the entries in the given dictionary
	// resetting the parentDict to this dictionary

	for (IDLList<entry>::const_iterator iter = (rhs).begin(); iter != (rhs).end(); ++iter)
	{
		add(iter().clone(*this).ptr());
	}
}


void AutLib::dictionary::operator+=(const dictionary& rhs)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorIn("dictionary::operator+=(const dictionary&)")
			<< "attempted addition assignment to self for dictionary " << name()
			<< abort(FatalError);
	}

	for (IDLList<entry>::const_iterator iter = (rhs).begin(); iter != (rhs).end(); ++iter)
	{
		add(iter().clone(*this).ptr());
	}
}


void AutLib::dictionary::operator|=(const dictionary& rhs)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorIn("dictionary::operator|=(const dictionary&)")
			<< "attempted assignment to self for dictionary " << name()
			<< abort(FatalError);
	}

	for (IDLList<entry>::const_iterator iter = (rhs).begin(); iter != (rhs).end(); ++iter)
	{
		if (!found(iter().keyword()))
		{
			add(iter().clone(*this).ptr());
		}
	}
}


void AutLib::dictionary::operator<<=(const dictionary& rhs)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorIn("dictionary::operator<<=(const dictionary&)")
			<< "attempted assignment to self for dictionary " << name()
			<< abort(FatalError);
	}

	for (IDLList<entry>::const_iterator iter = (rhs).begin(); iter != (rhs).end(); ++iter)
	{
		set(iter().clone(*this).ptr());
	}
}

namespace AutLib
{
	dictionary operator+(const dictionary& dict1, const dictionary& dict2)
	{
		dictionary sum(dict1);
		sum += dict2;
		return sum;
	}


	dictionary operator|(const dictionary& dict1, const dictionary& dict2)
	{
		dictionary sum(dict1);
		sum |= dict2;
		return sum;
	}
}