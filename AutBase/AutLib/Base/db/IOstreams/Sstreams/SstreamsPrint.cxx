#include <ISstream.hxx>
#include <OSstream.hxx>

void AutLib::ISstream::print(Ostream& os) const
{
	os << "ISstream: " << name().c_str() << ' ';

	IOstream::print(os);
	IOstream::print(os, is_.rdstate());
}


void AutLib::OSstream::print(Ostream& os) const
{
	os << "OSstream: " << name().c_str() << ' ';

	IOstream::print(os);
	IOstream::print(os, os_.rdstate());
}