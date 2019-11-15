#include <Leg_PropNo1_CamberForm.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_CamberForm::Defaults()
{
	RootCamber() = std::make_shared<Leg_Model_ConstParam>(DP::CAMBER_ROOT.Index(), DP::CAMBER_ROOT.Name(), DP::CAMBER_ROOT.Value());
	TipCamber() = std::make_shared<Leg_Model_ConstParam>(DP::CAMBER_TIP.Index(), DP::CAMBER_TIP.Name(), DP::CAMBER_TIP.Value());
	MaxCamber() = std::make_shared<Leg_Model_ConstParam>(DP::CAMBER_MAX.Index(), DP::CAMBER_MAX.Name(), DP::CAMBER_MAX.Value());
	MaxCamberLocation() = std::make_shared<Leg_Model_BndParam>(DP::CAMBER_MAX_LOCATION.Index(), DP::CAMBER_MAX_LOCATION.Name(), DP::CAMBER_MAX_LOCATION.Value(), 0, 1);
	RootWeight() = std::make_shared<Leg_Model_BndParam>(DP::CAMBER_ROOT_WEIGHT.Index(), DP::CAMBER_ROOT_WEIGHT.Name(), DP::CAMBER_ROOT_WEIGHT.Value(), 0, 1);
	TipWeight() = std::make_shared<Leg_Model_BndParam>(DP::CAMBER_TIP_WEIGHT.Index(), DP::CAMBER_TIP_WEIGHT.Name(), DP::CAMBER_TIP_WEIGHT.Value(), 0, 1);
}

AutLib::Leg_PropNo1_CamberForm::Leg_PropNo1_CamberForm()
{
	Defaults();
}