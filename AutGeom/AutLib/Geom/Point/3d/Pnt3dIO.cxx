#include <Pnt3d.hxx>

#include <token.hxx>
#include <OFstream.hxx>

void AutLib::Pnt3d::Print(std::ostream & os) const
{
	os << *this;
}

void AutLib::Pnt3d::AddToPlt(OFstream & theFile) const
{
	theFile << X() << "  " << Y() << "  " << Z();
}

namespace AutLib
{

	std::ostream & operator<<(std::ostream & os, const Pnt3d & P)
	{
		os << P.X() << ",  " << P.Y() << ",  " << P.Z();
		return os;
	}

	std::istream & AutLib::operator>>(std::istream & is, Pnt3d & P)
	{
		Standard_Real x, y, z;
		std::string comma;

		is >> x;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> y;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		is >> comma;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a comma parameter"
				<< abort(FatalError);
		}

		is >> z;
		if (!is.good())
		{
			FatalErrorIn(FunctionSIG)
				<< "Error in reading a real parameter"
				<< abort(FatalError);
		}

		P.SetCoord(x, y, z);
		return is;
	}

	Ostream & operator<<(Ostream & os, const Pnt3d & P)
	{
		os << token::BEGIN_LIST;
		os 
			<< P.X() 
			<< token::COMMA 
			<< token::SPACE 
			<< P.Y() 
			<< token::COMMA 
			<< token::SPACE 
			<< P.Z();
		os << token::END_LIST;

		// Check state of Ostream
		os.check(FunctionSIG);
		return os;
	}

	Istream & AutLib::operator>>(Istream & is, Pnt3d & P)
	{
		Standard_Real x, y, z;
		string comma;

		is.readBegin(FunctionSIG);
		is >> x >> comma >> y >> comma >> z;
		is.readEnd(FunctionSIG);

		// Check state of Istream
		is.check(FunctionSIG);
		return is;
	}
}