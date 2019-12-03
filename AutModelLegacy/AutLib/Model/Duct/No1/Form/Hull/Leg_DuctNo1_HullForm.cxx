#include <Leg_DuctNo1_HullForm.hxx>

#include <Leg_DuctNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_DuctNo1_Defaults DP;

void AutLib::Leg_DuctNo1_HullForm::Defaults()
{
	Inlet().Width() = std::make_shared<Leg_Model_BndParam>(DP::INLET_WIDTH.Index(), DP::INLET_WIDTH.Name(), DP::INLET_WIDTH.Value(), 0, 1);
	Inlet().SideSlope() = std::make_shared<Leg_Model_BndParam>(DP::INLET_SIDE_SLOPE.Index(), DP::INLET_SIDE_SLOPE.Name(), DP::INLET_SIDE_SLOPE.Value(), 0, 1);
	Inlet().LowerTightness() = std::make_shared<Leg_Model_BndParam>(DP::INLET_LOWER_TIGHTNESS.Index(), DP::INLET_LOWER_TIGHTNESS.Name(), DP::INLET_LOWER_TIGHTNESS.Value(), 0, 1);
	Inlet().UpperTightness() = std::make_shared<Leg_Model_BndParam>(DP::INLET_UPPER_TIGHTNESS.Index(), DP::INLET_UPPER_TIGHTNESS.Name(), DP::INLET_UPPER_TIGHTNESS.Value(), 0, 1);

	Mid().Width() = std::make_shared<Leg_Model_BndParam>(DP::MID_WIDTH.Index(), DP::MID_WIDTH.Name(), DP::MID_WIDTH.Value(), 0, 1);
	Mid().SideSlope() = std::make_shared<Leg_Model_BndParam>(DP::MID_SIDE_SLOPE.Index(), DP::MID_SIDE_SLOPE.Name(), DP::MID_SIDE_SLOPE.Value(), 0, 1);
	Mid().LowerTightness() = std::make_shared<Leg_Model_BndParam>(DP::MID_LOWER_TIGHTNESS.Index(), DP::MID_LOWER_TIGHTNESS.Name(), DP::MID_LOWER_TIGHTNESS.Value(), 0, 1);
	Mid().UpperTightness() = std::make_shared<Leg_Model_BndParam>(DP::MID_UPPER_TIGHTNESS.Index(), DP::MID_UPPER_TIGHTNESS.Name(), DP::MID_UPPER_TIGHTNESS.Value(), 0, 1);

	Outlet().Width() = std::make_shared<Leg_Model_BndParam>(DP::OUTLET_WIDTH.Index(), DP::OUTLET_WIDTH.Name(), DP::OUTLET_WIDTH.Value(), 0, 1);
	Outlet().SideSlope() = std::make_shared<Leg_Model_BndParam>(DP::OUTLET_SIDE_SLOPE.Index(), DP::OUTLET_SIDE_SLOPE.Name(), DP::OUTLET_SIDE_SLOPE.Value(), 0, 1);
	Outlet().LowerTightness() = std::make_shared<Leg_Model_BndParam>(DP::OUTLET_LOWER_TIGHTNESS.Index(), DP::OUTLET_LOWER_TIGHTNESS.Name(), DP::OUTLET_LOWER_TIGHTNESS.Value(), 0, 1);
	Outlet().UpperTightness() = std::make_shared<Leg_Model_BndParam>(DP::OUTLET_UPPER_TIGHTNESS.Index(), DP::OUTLET_UPPER_TIGHTNESS.Name(), DP::OUTLET_UPPER_TIGHTNESS.Value(), 0, 1);

	MidLocation() = std::make_shared<Leg_Model_BndParam>(DP::MID_LOCATION.Index(), DP::MID_LOCATION.Name(), DP::MID_LOCATION.Value(), 0, 1);
}

AutLib::Leg_DuctNo1_HullForm::Leg_DuctNo1_HullForm()
{
	Defaults();
}