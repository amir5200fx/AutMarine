#include <Marine_DimensionSet.hxx>

#include <token.hxx>

namespace AutLib
{

	Ostream& AutLib::operator<<(Ostream& os, const Marine_DimensionSet& dset)
	{
		os << token::BEGIN_SQR;

		for (int Dimension = 0; Dimension < Marine_DimensionSet::nbDimensions - 1; Dimension++)
		{
			os << dset.theExponents_[Dimension] << token::SPACE;
		}
		os << dset.theExponents_[Marine_DimensionSet::nbDimensions - 1] << token::END_SQR;

		// Check state of Ostream
		os.check("Ostream& operator<<(Ostream&, const Marine_DimensionSet&)");

		return os;
	}
}