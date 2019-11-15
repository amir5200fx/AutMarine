#include <Leg_PropNo1_ThicknessForm.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_ThicknessForm::Defaults()
{
	RootThickness() = std::make_shared<Leg_Model_ConstParam>(DP::THICK_ROOT.Index(), DP::THICK_ROOT.Name(), DP::THICK_ROOT.Value());
	TipThickness() = std::make_shared<Leg_Model_ConstParam>(DP::THICK_TIP.Index(), DP::THICK_TIP.Name(), DP::THICK_TIP.Value());
	RootSteep() = std::make_shared<Leg_Model_BndParam>(DP::THICK_ROOT_STEEP.Index(), DP::THICK_ROOT_STEEP.Name(), DP::THICK_ROOT_STEEP.Value(), 0, 1);
	TipSteep() = std::make_shared<Leg_Model_BndParam>(DP::THICK_TIP_STEEP.Index(), DP::THICK_TIP_STEEP.Name(), DP::THICK_TIP_STEEP.Value(), 0, 1);
}

AutLib::Leg_PropNo1_ThicknessForm::Leg_PropNo1_ThicknessForm()
{
	Defaults();
}