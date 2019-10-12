#include <Marine_DimensionSet.hxx>

#include <error.hxx>
#include <OSstream.hxx>

const AutLib::word AutLib::Marine_DimensionSet::typeName(AutLib::Marine_DimensionSet::typeName_());
AutLib::debug::debugSwitch AutLib::Marine_DimensionSet::debug(std::string(AutLib::Marine_DimensionSet::typeName_()), 1, "");
const Standard_Real AutLib::Marine_DimensionSet::smallExponent = (Standard_Real)SMALL;

AutLib::Marine_DimensionSet::Marine_DimensionSet
(
	const Standard_Real mass,
	const Standard_Real length,
	const Standard_Real time,
	const Standard_Real temperature
)
{
	theExponents_[MASS] = mass;
	theExponents_[LENGTH] = length;
	theExponents_[TIME] = time;
	theExponents_[TEMPERATURE] = temperature;
}

Standard_Boolean AutLib::Marine_DimensionSet::DimensionLess() const
{
	Standard_Boolean Dimensionless = Standard_True;

	for (Standard_Integer Dimension = 0; Dimension < nbDimensions; Dimension++)
	{
		Dimensionless = Dimensionless &&
			(
				theExponents_[Dimension] < smallExponent
				&& theExponents_[Dimension] > -smallExponent
				);
	}

	return Dimensionless;
}

void AutLib::Marine_DimensionSet::Reset(const Marine_DimensionSet& ds)
{
	for (int Dimension = 0; Dimension < nbDimensions; Dimension++)
	{
		theExponents_[Dimension] = ds.theExponents_[Dimension];
	}
}

Standard_Boolean AutLib::Marine_DimensionSet::operator==(const Marine_DimensionSet& ds) const
{
	Standard_Boolean equall = Standard_True;

	for (Standard_Integer Dimension = 0; Dimension < nbDimensions; Dimension++)
	{
		equall = equall &&
			(mag(theExponents_[Dimension] - ds.theExponents_[Dimension])
				< smallExponent);
	}

	return equall;
}

Standard_Boolean AutLib::Marine_DimensionSet::operator!=(const Marine_DimensionSet& ds) const
{
	return !(operator==(ds));
}

Standard_Boolean AutLib::Marine_DimensionSet::operator=(const Marine_DimensionSet& ds) const
{
	if (Marine_DimensionSet::debug && *this != ds)
	{
		FatalErrorIn("Marine_DimensionSet::operator=(const Marine_DimensionSet& ds) const")
			<< "Different dimensions for =" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return Standard_True;
}

Standard_Boolean AutLib::Marine_DimensionSet::operator+=(const Marine_DimensionSet& ds) const
{
	if (Marine_DimensionSet::debug && *this != ds)
	{
		FatalErrorIn("Marine_DimensionSet::operator+=(const Marine_DimensionSet& ds) const")
			<< "Different dimensions for +=" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return Standard_True;
}

Standard_Boolean AutLib::Marine_DimensionSet::operator-=(const Marine_DimensionSet& ds) const
{
	if (Marine_DimensionSet::debug && *this != ds)
	{
		FatalErrorIn("Marine_DimensionSet::operator-=(const Marine_DimensionSet& ds) const")
			<< "Different dimensions for -=" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return Standard_True;
}

Standard_Boolean AutLib::Marine_DimensionSet::operator*=(const Marine_DimensionSet& ds)
{
	Reset((*this) * ds);

	return Standard_True;
}

Standard_Boolean AutLib::Marine_DimensionSet::operator/=(const Marine_DimensionSet& ds)
{
	Reset((*this) / ds);

	return Standard_True;
}

AutLib::Marine_DimensionSet AutLib::max(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)
{
	if (Marine_DimensionSet::debug && ds1 != ds2)
	{
		FatalErrorIn("max(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)")
			<< "Arguments of max have different dimensions" << endl
			<< "     dimensions : " << ds1 << " and " << ds2 << endl
			<< abort(FatalError);
	}

	return ds1;
}

AutLib::Marine_DimensionSet AutLib::min(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)
{
	if (Marine_DimensionSet::debug && ds1 != ds2)
	{
		FatalErrorIn("min(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)")
			<< "Arguments of min have different dimensions" << endl
			<< "     dimensions : " << ds1 << " and " << ds2 << endl
			<< abort(FatalError);
	}

	return ds1;
}

AutLib::Marine_DimensionSet AutLib::pow(const Marine_DimensionSet& ds, const scalar p)
{
	Marine_DimensionSet dimPow
	(
		ds[Marine_DimensionSet::MASS] * p,
		ds[Marine_DimensionSet::LENGTH] * p,
		ds[Marine_DimensionSet::TIME] * p,
		ds[Marine_DimensionSet::TEMPERATURE] * p
	);

	return dimPow;
}

AutLib::Marine_DimensionSet AutLib::sqr(const Marine_DimensionSet& ds)
{
	return pow(ds, 2);
}

AutLib::Marine_DimensionSet AutLib::pow3(const Marine_DimensionSet& ds)
{
	return pow(ds, 3);
}

AutLib::Marine_DimensionSet AutLib::pow4(const Marine_DimensionSet& ds)
{
	return pow(ds, 4);
}

AutLib::Marine_DimensionSet AutLib::pow5(const Marine_DimensionSet& ds)
{
	return pow(ds, 5);
}

AutLib::Marine_DimensionSet AutLib::pow6(const Marine_DimensionSet& ds)
{
	return pow(ds, 6);
}

AutLib::Marine_DimensionSet AutLib::sqrt(const Marine_DimensionSet& ds)
{
	return pow(ds, 0.5);
}

AutLib::Marine_DimensionSet AutLib::magSqr(const Marine_DimensionSet& ds)
{
	return pow(ds, 2);
}

AutLib::Marine_DimensionSet AutLib::mag(const Marine_DimensionSet& ds)
{
	return ds;
}

AutLib::Marine_DimensionSet AutLib::sign(const Marine_DimensionSet&)
{
	return marineLib::dimless;
}

AutLib::Marine_DimensionSet AutLib::pos(const Marine_DimensionSet&)
{
	return marineLib::dimless;
}

AutLib::Marine_DimensionSet AutLib::neg(const Marine_DimensionSet&)
{
	return marineLib::dimless;
}

AutLib::Marine_DimensionSet AutLib::inv(const Marine_DimensionSet& ds)
{
	return marineLib::dimless / ds;
}

AutLib::Marine_DimensionSet AutLib::hinv(const Marine_DimensionSet& ds)
{
	return inv(ds);
}

namespace AutLib
{
	Marine_DimensionSet AutLib::operator-(const Marine_DimensionSet& ds)
	{
		return ds;
	}

	Marine_DimensionSet AutLib::operator+(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)
	{
		Marine_DimensionSet dimSum(ds1);

		if (Marine_DimensionSet::debug && ds1 != ds2)
		{
			FatalErrorIn
			("operator+(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)")
				<< "LHS and RHS of + have different dimensions" << endl
				<< "     dimensions : " << ds1 << " + " << ds2 << endl
				<< abort(FatalError);
		}

		return dimSum;
	}

	Marine_DimensionSet AutLib::operator-(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)
	{
		Marine_DimensionSet dimDifference(ds1);

		if (Marine_DimensionSet::debug && ds1 != ds2)
		{
			FatalErrorIn
			("operator-(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)")
				<< "LHS and RHS of - have different dimensions" << endl
				<< "     dimensions : " << ds1 << " - " << ds2 << endl
				<< abort(FatalError);
		}

		return dimDifference;
	}

	Marine_DimensionSet AutLib::operator*(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)
	{
		Marine_DimensionSet dimProduct(ds1);

		for (int Dimension = 0; Dimension < Marine_DimensionSet::nbDimensions; Dimension++)
		{
			dimProduct.theExponents_[Dimension] += ds2.theExponents_[Dimension];
		}

		return dimProduct;
	}

	Marine_DimensionSet AutLib::operator/(const Marine_DimensionSet& ds1, const Marine_DimensionSet& ds2)
	{
		Marine_DimensionSet dimQuotient(ds1);

		for (int Dimension = 0; Dimension < Marine_DimensionSet::nbDimensions; Dimension++)
		{
			dimQuotient.theExponents_[Dimension] -= ds2.theExponents_[Dimension];
		}

		return dimQuotient;
	}
}