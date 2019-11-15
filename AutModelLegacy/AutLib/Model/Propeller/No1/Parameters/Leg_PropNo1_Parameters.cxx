#include <Leg_PropNo1_Parameters.hxx>

#include <Leg_PropNo1_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_PropNo1_Defaults DP;

void AutLib::Leg_PropNo1_Parameters::Defaults()
{
	NbSections() = DP::NB_SECTIONS;
	NbBlades() = DP::NB_BLADES;
	NbSpans() = DP::NB_SPANS;

	RemoveHubApex_ = Standard_False;

	Diameter() = std::make_shared<Leg_Model_ConstParam>(DP::DIAMETER.Index(), DP::DIAMETER.Name(), DP::DIAMETER.Value());
	HubRadius() = std::make_shared<Leg_Model_ConstParam>(DP::HUB_RADIUS.Index(), DP::HUB_RADIUS.Name(), DP::HUB_RADIUS.Value());

	TipGap() = std::make_shared<Leg_Model_ConstParam>(DP::TIP_GAP.Index(), DP::TIP_GAP.Name(), DP::TIP_GAP.Value());
	TEGap() = std::make_shared<Leg_Model_ConstParam>(DP::TE_GAP.Index(), DP::TE_GAP.Name(), DP::TE_GAP.Value());
}

AutLib::Leg_PropNo1_Parameters::Leg_PropNo1_Parameters()
{
	Defaults();
}