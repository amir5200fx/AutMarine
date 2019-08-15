#include <IPstream.hxx>
#include <OPstream.hxx>

void AutLib::IPstream::print(Ostream& os) const
{
	os << "Reading from processor " << fromProcNo_
		<< " to processor " << myProcNo() << AutLib::endl;
}


void AutLib::OPstream::print(Ostream& os) const
{
	os << "Writing from processor " << toProcNo_
		<< " to processor " << myProcNo() << AutLib::endl;
}