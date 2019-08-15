#include <labelSymmTensor.hxx>

namespace AutLib
{
	template<>
	const char* const labelSymmTensor::typeName = "labelSymmTensor";

	template<>
	const char* labelSymmTensor::componentNames[] =
	{
		"xx", "xy", "xz",
			  "yy", "yz",
					"zz"
	};

	template<>
	const labelSymmTensor labelSymmTensor::zero
	(
		0, 0, 0,
		0, 0,
		0
	);

	template<>
	const labelSymmTensor labelSymmTensor::one
	(
		1, 1, 1,
		1, 1,
		1
	);
}