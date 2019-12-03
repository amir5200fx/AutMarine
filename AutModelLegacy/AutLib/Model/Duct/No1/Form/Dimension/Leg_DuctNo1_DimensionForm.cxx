#include <Leg_DuctNo1_DimensionForm.hxx>

#include <Leg_DuctNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_DuctNo1_Defaults DP;

void AutLib::Leg_DuctNo1_DimensionForm::Defaults()
{
	HeightAtOutlet() = std::make_shared<Leg_Model_ConstParam>(DP::HEIGHT_AT_OUTLET.Index(), DP::HEIGHT_AT_OUTLET.Name(), DP::HEIGHT_AT_OUTLET.Value());
	OveralLength() = std::make_shared<Leg_Model_ConstParam>(DP::OVERAL_LENGTH.Index(), DP::OVERAL_LENGTH.Name(), DP::OVERAL_LENGTH.Value());
	BreadthAtInlet() = std::make_shared<Leg_Model_ConstParam>(DP::BREADTH_AT_INLET.Index(), DP::BREADTH_AT_INLET.Name(), DP::BREADTH_AT_INLET.Value());
	BreadthAtOutlet() = std::make_shared<Leg_Model_ConstParam>(DP::BREADTH_AT_OUTLET.Index(), DP::BREADTH_AT_OUTLET.Name(), DP::BREADTH_AT_OUTLET.Value());
	DepthAtInlet() = std::make_shared<Leg_Model_ConstParam>(DP::DEPTH_AT_INLET.Index(), DP::DEPTH_AT_INLET.Name(), DP::DEPTH_AT_INLET.Value());
	DepthAtOutlet() = std::make_shared<Leg_Model_ConstParam>(DP::DEPTH_AT_OUTLET.Index(), DP::DEPTH_AT_OUTLET.Name(), DP::DEPTH_AT_OUTLET.Value());

	NbSections() = DP::NB_SECTIONS;
}

AutLib::Leg_DuctNo1_DimensionForm::Leg_DuctNo1_DimensionForm()
{
	Defaults();
}