#include <labelVector.hxx>

template<>
const char* const AutLib::labelVector::typeName = "labelVector";

template<>
const char* AutLib::labelVector::componentNames[] = { "x", "y", "z" };

template<>
const AutLib::labelVector AutLib::labelVector::zero(0, 0, 0);

template<>
const AutLib::labelVector AutLib::labelVector::one(1, 1, 1);