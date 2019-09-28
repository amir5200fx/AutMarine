#include <CrvMakerFreedom_xDir.hxx>

#include <CrvMaker_FixedParameter.hxx>
#include <CrvMaker_FreeParameter.hxx>S
#include <CrvMaker_Constant.hxx>

Standard_Real AutLib::CrvMakerFreedom_xDir<AutLib::CrvMaker_Constant>::Value() const
{
	Debug_Null_Pointer(theValue_);
	return theValue_->Value();
}

Standard_Real AutLib::CrvMakerFreedom_xDir<AutLib::CrvMaker_FixedParameter>::Value() const
{
	Debug_Null_Pointer(theValue_);
	return theValue_->Value();
}

Standard_Real 
AutLib::CrvMakerFreedom_xDir<AutLib::CrvMaker_FreeParameter>::Value
(
	const Standard_Real t
) const
{
	Debug_Null_Pointer(theParameter_);
	Debug_Null_Pointer(theBoundary_);

	auto x0 = theBoundary_->Lower();
	auto x1 = theBoundary_->Upper();

	theParameter_->Update(t);
	auto p = theParameter_->Value();

	return x0 + (x1 - x0) * p;
}