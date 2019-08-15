#include <SHA1Digest.hxx>

#include <cstring>

const char hexChars[] = "0123456789abcdef";

AutLib::SHA1Digest::SHA1Digest()
{
	clear();
}

void AutLib::SHA1Digest::clear()
{
	memset(v_, 0, length);
}

bool AutLib::SHA1Digest::operator==(const SHA1Digest& rhs) const
{
	for (unsigned i = 0; i < length; ++i)
	{
		if (v_[i] != rhs.v_[i])
		{
			return false;
		}
	}

	return true;
}


bool AutLib::SHA1Digest::operator!=(const SHA1Digest& rhs) const
{
	return !operator==(rhs);
}