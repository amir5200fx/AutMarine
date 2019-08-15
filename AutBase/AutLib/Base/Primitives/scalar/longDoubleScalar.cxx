#include <longDoubleScalar.hxx>

#include <token.hxx>
#include <Istream.hxx>

#include <sstream>

namespace AutLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const char* const pTraits<longDoubleScalar>::typeName = "scalar";
	const longDoubleScalar pTraits<longDoubleScalar>::zero = 0.0;
	const longDoubleScalar pTraits<longDoubleScalar>::one = 1.0;
	const longDoubleScalar pTraits<longDoubleScalar>::min = -longDoubleScalarVSMALL;
	const longDoubleScalar pTraits<longDoubleScalar>::max = longDoubleScalarVGREAT;

	const char* pTraits<longDoubleScalar>::componentNames[] = { "x" };

	pTraits<longDoubleScalar>::pTraits(Istream& is)
	{
		is >> p_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	word name(const longDoubleScalar val)
	{
		std::ostringstream buf;
		buf << val;
		return buf.str();
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	longDoubleScalar readLongDoubleScalar(Istream& is)
	{
		longDoubleScalar rs;
		is >> rs;

		return rs;
	}


	Istream& operator>>(Istream& is, longDoubleScalar& s)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isNumber())
		{
			s = t.number();
		}
		else
		{
			is.setBad();
			FatalIOErrorIn("operator>>(Istream&, longDoubleScalar&)", is)
				<< "wrong token type - expected longDoubleScalar found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, longDoubleScalar&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const longDoubleScalar s)
	{
		os.write(s);
		os.check("Ostream& operator<<(Ostream&, const longDoubleScalar&)");
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace AutLib