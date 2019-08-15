#include <IStringStream.hxx>
#include <OStringStream.hxx>

void AutLib::IStringStream::print(Ostream& os) const
{
	os << "IStringStream " << name() << " : "
		<< "buffer = \n" << str() << AutLib::endl;

	ISstream::print(os);
}


void AutLib::OStringStream::print(Ostream& os) const
{
	os << "OStringStream " << name() << " : "
		<< "buffer = \n" << str() << AutLib::endl;

	OSstream::print(os);
}