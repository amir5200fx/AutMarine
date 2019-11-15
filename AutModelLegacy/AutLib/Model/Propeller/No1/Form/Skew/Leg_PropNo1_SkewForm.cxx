#include <Leg_PropNo1_SkewForm.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_SkewForm::Defaults()
{
	TipSkew() = std::make_shared<Leg_Model_ConstParam>(DP::SKEW_TIP.Index(), DP::SKEW_TIP.Name(), DP::SKEW_TIP.Value());
	TipSteep() = std::make_shared<Leg_Model_BndParam>(DP::SKEW_TIP_STEEP.Index(), DP::SKEW_TIP_STEEP.Name(), DP::SKEW_TIP_STEEP.Value(), 0, 1);
	RootSteep() = std::make_shared<Leg_Model_BndParam>(DP::SKEW_ROOT_STEEP.Index(), DP::SKEW_ROOT_STEEP.Name(), DP::SKEW_ROOT_STEEP.Value(), 0, 1);
}

AutLib::Leg_PropNo1_SkewForm::Leg_PropNo1_SkewForm()
{
	Defaults();
}