#include <IOdictionary.hxx>

bool AutLib::IOdictionary::readData(Istream& is)
{
	is >> *this;
	return !is.bad();
}


bool AutLib::IOdictionary::writeData(Ostream& os) const
{
	dictionary::write(os, false);
	return os.good();
}