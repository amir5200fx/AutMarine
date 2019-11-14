#include <Leg_PropNo1_HubForm.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_HubForm::Defaults()
{
	HubLength() = std::make_shared<Leg_Model_ConstParam>(DP::HUB_LENGTH.Index(), DP::HUB_LENGTH.Name(), DP::HUB_LENGTH.Value());
	HubWeight() = std::make_shared<Leg_Model_BndParam>(DP::HUB_WEIGHT.Index(), DP::HUB_WEIGHT.Name(), DP::HUB_WEIGHT.Value(), 0 , 1);
	ShaftRadius() = std::make_shared<Leg_Model_ConstParam>(DP::SHAFT_RADIUS.Index(), DP::SHAFT_RADIUS.Name(), DP::SHAFT_RADIUS.Value());
	ShaftOffset() = std::make_shared<Leg_Model_ConstParam>(DP::SHAFT_OFFSET.Index(), DP::SHAFT_OFFSET.Name(), DP::SHAFT_OFFSET.Value());
	ShaftLength() = std::make_shared<Leg_Model_ConstParam>(DP::SHAFT_LENGTH.Index(), DP::SHAFT_LENGTH.Name(), DP::SHAFT_LENGTH.Value());
}

AutLib::Leg_PropNo1_HubForm::Leg_PropNo1_HubForm()
{
	Defaults();
}