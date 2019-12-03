#include <Leg_DuctNo1_BreadthForm.hxx>

#include <Leg_DuctNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_DuctNo1_Defaults DP;

void AutLib::Leg_DuctNo1_BreadthForm::Defaults()
{
	InletOffset() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_INLET_OFFSET.Index(), DP::BREADTH_INLET_OFFSET.Name(), DP::BREADTH_INLET_OFFSET.Value(), 0, 1);
	InletRiseWeight() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_INLET_RISE_WEIGHT.Index(), DP::BREADTH_INLET_RISE_WEIGHT.Name(), DP::BREADTH_INLET_RISE_WEIGHT.Value(), 0, 1);
	InletWeight() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_INLET_WEIGHT.Index(), DP::BREADTH_INLET_WEIGHT.Name(), DP::BREADTH_INLET_WEIGHT.Value(), 0, 1);
	LeftTurningPosition() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_LEFT_TURNING_POSITION.Index(), DP::BREADTH_LEFT_TURNING_POSITION.Name(), DP::BREADTH_LEFT_TURNING_POSITION.Value(), 0, 1);
	LeftTurningWidth() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_LEFT_TURNING_WIDTH.Index(), DP::BREADTH_LEFT_TURNING_WIDTH.Name(), DP::BREADTH_LEFT_TURNING_WIDTH.Value(), 0, 1);
	MidOffset() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_MID_OFFSET.Index(), DP::BREADTH_MID_OFFSET.Name(), DP::BREADTH_MID_OFFSET.Value(), 0, 1);
	MidWidth() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_MID_WIDTH.Index(), DP::BREADTH_MID_WIDTH.Name(), DP::BREADTH_MID_WIDTH.Value(), 0, 1);
	OutletOffset() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_OUTLET_OFFSET.Index(), DP::BREADTH_OUTLET_OFFSET.Name(), DP::BREADTH_OUTLET_OFFSET.Value(), 0, 1);
	OutletRiseWeight() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_OUTLET_RISE_WEIGTH.Index(), DP::BREADTH_OUTLET_RISE_WEIGTH.Name(), DP::BREADTH_OUTLET_RISE_WEIGTH.Value(), 0, 1);
	OutletWeight() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_OUTLET_WEIGHT.Index(), DP::BREADTH_OUTLET_WEIGHT.Name(), DP::BREADTH_OUTLET_WEIGHT.Value(), 0, 1);
	RightTurningPosition() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_RIGHT_TURNING_POSITION.Index(), DP::BREADTH_RIGHT_TURNING_POSITION.Name(), DP::BREADTH_RIGHT_TURNING_POSITION.Value(), 0, 1);
	RightTurningWidth() = std::make_shared<Leg_Model_BndParam>(DP::BREADTH_RIGHT_TURNING_WIDTH.Index(), DP::BREADTH_RIGHT_TURNING_WIDTH.Name(), DP::BREADTH_RIGHT_TURNING_WIDTH.Value(), 0, 1);
}

AutLib::Leg_DuctNo1_BreadthForm::Leg_DuctNo1_BreadthForm()
{
	Defaults();
}