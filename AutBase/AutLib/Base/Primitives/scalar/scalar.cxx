#include <scalar.hxx>

namespace AutLib
{

	scalar readScalar(Istream& is)
	{
		scalar rs;
		is >> rs;

		return rs;
	}
}