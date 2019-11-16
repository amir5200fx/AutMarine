#include <Leg_DuctNo1_GeneratorForm.hxx>

#include <Leg_DuctNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_DuctNo1_Defaults DP;

void AutLib::Leg_DuctNo1_GeneratorForm::Defaults()
{
	Position() = std::make_shared<Leg_Model_BndParam>(DP::GEN_POSITION.Index(), DP::GEN_POSITION.Name(), DP::GEN_POSITION.Value(), 0, 1);
	RisePoint() = std::make_shared<Leg_Model_BndParam>(DP::GEN_RISE_POINT.Index(), DP::GEN_RISE_POINT.Name(), DP::GEN_RISE_POINT.Value(), 0, 1);
	RiseTangent() = std::make_shared<Leg_Model_BndParam>(DP::GEN_RISE_TANGENT.Index(), DP::GEN_RISE_TANGENT.Name(), DP::GEN_RISE_TANGENT.Value(), 0, 1);
	OutletTangent() = std::make_shared<Leg_Model_BndParam>(DP::GEN_OUTLET_TANGENT.Index(), DP::GEN_OUTLET_TANGENT.Name(), DP::GEN_OUTLET_TANGENT.Value(), 0, 1);
}

AutLib::Leg_DuctNo1_GeneratorForm::Leg_DuctNo1_GeneratorForm()
{
	Defaults();
}