#include <Leg_PropNo1_RakeForm.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_RakeForm::Defaults()
{
	TipRake() = std::make_shared<Leg_Model_ConstParam>(DP::RAKE.Index(), DP::RAKE.Name(), DP::RAKE.Value());
}

AutLib::Leg_PropNo1_RakeForm::Leg_PropNo1_RakeForm()
{
	Defaults();
}