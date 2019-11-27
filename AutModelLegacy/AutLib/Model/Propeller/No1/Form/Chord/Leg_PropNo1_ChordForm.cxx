#include <Leg_PropNo1_ChordForm.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_ChordForm::Defaults()
{
	RootChord() = std::make_shared<Leg_Model_ConstParam>(DP::CHORD_ROOT.Index(), DP::CHORD_ROOT.Name(), DP::CHORD_ROOT.Value());
	TipChord() = std::make_shared<Leg_Model_ConstParam>(DP::CHORD_TIP.Index(), DP::CHORD_TIP.Name(), DP::CHORD_TIP.Value());
	MaxChord() = std::make_shared<Leg_Model_ConstParam>(DP::CHORD_MAX.Index(), DP::CHORD_MAX.Name(), DP::CHORD_MAX.Value());
	MaxChordLocation() = std::make_shared<Leg_Model_BndParam>(DP::CHORD_MAX_LOCATION.Index(), DP::CHORD_MAX_LOCATION.Name(), DP::CHORD_MAX_LOCATION.Value(), 0, 1);
	RootWeight() = std::make_shared<Leg_Model_BndParam>(DP::CHORD_ROOT_WEIGHT.Index(), DP::CHORD_ROOT_WEIGHT.Name(), DP::CHORD_ROOT_WEIGHT.Value(), 0 , 1);
	TipWeight() = std::make_shared<Leg_Model_BndParam>(DP::CHORD_TIP_WEIGHT.Index(), DP::CHORD_TIP_WEIGHT.Name(), DP::CHORD_TIP_WEIGHT.Value(), 0, 1);
}

AutLib::Leg_PropNo1_ChordForm::Leg_PropNo1_ChordForm()
{
	Defaults();
}