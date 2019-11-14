#include <Leg_PropNo1_PitchForm.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_PitchForm::Defaults()
{
	RootPitch() = std::make_shared<Leg_Model_ConstParam>(DP::PITCH_ROOT.Index(), DP::PITCH_ROOT.Name(), DP::PITCH_ROOT.Value());
	TipPitch() = std::make_shared<Leg_Model_ConstParam>(DP::PITCH_TIP.Index(), DP::PITCH_TIP.Name(), DP::PITCH_TIP.Value());
	RootSteep() = std::make_shared<Leg_Model_BndParam>(DP::PITCH_ROOT_STEEP.Index(), DP::PITCH_ROOT_STEEP.Name(), DP::PITCH_ROOT_STEEP.Value(), 0, 1);
	TipSteep() = std::make_shared<Leg_Model_BndParam>(DP::PITCH_TIP_STEEP.Index(), DP::PITCH_TIP_STEEP.Name(), DP::PITCH_TIP_STEEP.Value(), 0, 1);
}