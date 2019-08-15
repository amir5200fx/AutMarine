#include <symmTensor2D.hxx>

namespace AutLib
{

	template<>
	const char* const symmTensor2D::typeName = "symmTensor2D";

	template<>
	const char* symmTensor2D::componentNames[] =
	{
		"xx", "xy",
			  "yy"
	};

	template<>
	const symmTensor2D symmTensor2D::zero
	(
		0, 0,
		0
	);

	template<>
	const symmTensor2D symmTensor2D::one
	(
		1, 1,
		1
	);

	template<>
	const symmTensor2D symmTensor2D::max
	(
		VGREAT, VGREAT,
		VGREAT
	);

	template<>
	const symmTensor2D symmTensor2D::min
	(
		-VGREAT, -VGREAT,
		-VGREAT
	);

	template<>
	const symmTensor2D symmTensor2D::I
	(
		1, 0,
		1
	);
}