#include <Leg_Nihad2_Parameters.hxx>

#include <Leg_Nihad2_Defaults.hxx>
#include <Leg_Model_ConstParam.hxx>
#include <Leg_Model_BndParam.hxx>

typedef AutLib::Leg_Nihad2_DefaultsParameters DP;

AutLib::Leg_Nihad2_Dimensions::Leg_Nihad2_Dimensions()
{
	theBeamOnDeck_ = std::make_shared<Leg_Model_ConstParam>(DP::BEAM_ON_DECK.Index(), DP::BEAM_ON_DECK.Name(), DP::BEAM_ON_DECK.Value());
	theDepthAtBow_ = std::make_shared<Leg_Model_ConstParam>(DP::DEPTH_AT_BOW.Index(), DP::DEPTH_AT_BOW.Name(), DP::DEPTH_AT_BOW.Value());
	theDepthAtTransom_ = std::make_shared<Leg_Model_ConstParam>(DP::DEPTH_AT_TRANSOM.Index(), DP::DEPTH_AT_TRANSOM.Name(), DP::DEPTH_AT_TRANSOM.Value());
	theLengthOnDeck_ = std::make_shared<Leg_Model_ConstParam>(DP::LENGTH_ON_DECK.Index(), DP::LENGTH_ON_DECK.Name(), DP::LENGTH_ON_DECK.Value());
	theTransomHeight_ = std::make_shared<Leg_Model_ConstParam>(DP::TRANSOM_HEIGHT.Index(), DP::TRANSOM_HEIGHT.Name(), DP::TRANSOM_HEIGHT.Value());

	theNbNetColumns_ = 9;
}

AutLib::Leg_Nihad2_AftSectionParams::Leg_Nihad2_AftSectionParams()
{
	Tightness0() = std::make_shared<Leg_Model_BndParam>(DP::AFT_TIGHTNESS0.Index(), DP::AFT_TIGHTNESS0.Name(), DP::AFT_TIGHTNESS0.Value(), 0, 1);
	Tightness1() = std::make_shared<Leg_Model_BndParam>(DP::AFT_TIGHTNESS1.Index(), DP::AFT_TIGHTNESS1.Name(), DP::AFT_TIGHTNESS1.Value(), 0, 1);
	Trim0() = std::make_shared<Leg_Model_BndParam>(DP::AFT_TRIM0.Index(), DP::AFT_TRIM0.Name(), DP::AFT_TRIM0.Value(), 0, 1);
	Trim1() = std::make_shared<Leg_Model_BndParam>(DP::AFT_TRIM1.Index(), DP::AFT_TRIM1.Name(), DP::AFT_TRIM1.Value(), 0, 1);
	Deadrise() = std::make_shared<Leg_Model_BndParam>(DP::AFT_DEADRISE.Index(), DP::AFT_DEADRISE.Name(), DP::AFT_DEADRISE.Value(), 0, 1);
	SideSlope() = std::make_shared<Leg_Model_BndParam>(DP::AFT_SIDE_SLOPE.Index(), DP::AFT_SIDE_SLOPE.Name(), DP::AFT_SIDE_SLOPE.Value(), 0, 1);
}

AutLib::Leg_Nihad2_FwdSectionParams::Leg_Nihad2_FwdSectionParams()
{
	Tightness0() = std::make_shared<Leg_Model_BndParam>(DP::FWD_TIGHTNESS0.Index(), DP::FWD_TIGHTNESS0.Name(), DP::FWD_TIGHTNESS0.Value(), 0, 1);
	Tightness1() = std::make_shared<Leg_Model_BndParam>(DP::FWD_TIGHTNESS1.Index(), DP::FWD_TIGHTNESS1.Name(), DP::FWD_TIGHTNESS1.Value(), 0, 1);
	Trim0() = std::make_shared<Leg_Model_BndParam>(DP::FWD_TRIM0.Index(), DP::FWD_TRIM0.Name(), DP::FWD_TRIM0.Value(), 0, 1);
	Trim1() = std::make_shared<Leg_Model_BndParam>(DP::FWD_TRIM1.Index(), DP::FWD_TRIM1.Name(), DP::FWD_TRIM1.Value(), 0, 1);
	Deadrise() = std::make_shared<Leg_Model_BndParam>(DP::FWD_DEADRISE.Index(), DP::FWD_DEADRISE.Name(), DP::FWD_DEADRISE.Value(), 0, 1);
	SideSlope() = std::make_shared<Leg_Model_BndParam>(DP::FWD_SIDE_SLOPE.Index(), DP::FWD_SIDE_SLOPE.Name(), DP::FWD_SIDE_SLOPE.Value(), 0, 1);
}

AutLib::Leg_Nihad2_MidSectionParams::Leg_Nihad2_MidSectionParams()
{
	Tightness0() = std::make_shared<Leg_Model_BndParam>(DP::MID_TIGHTNESS0.Index(), DP::MID_TIGHTNESS0.Name(), DP::MID_TIGHTNESS0.Value(), 0, 1);
	Tightness1() = std::make_shared<Leg_Model_BndParam>(DP::MID_TIGHTNESS1.Index(), DP::MID_TIGHTNESS1.Name(), DP::MID_TIGHTNESS1.Value(), 0, 1);
	Trim0() = std::make_shared<Leg_Model_BndParam>(DP::MID_TRIM0.Index(), DP::MID_TRIM0.Name(), DP::MID_TRIM0.Value(), 0, 1);
	Trim1() = std::make_shared<Leg_Model_BndParam>(DP::MID_TRIM1.Index(), DP::MID_TRIM1.Name(), DP::MID_TRIM1.Value(), 0, 1);
	Deadrise() = std::make_shared<Leg_Model_BndParam>(DP::MID_DEADRISE.Index(), DP::MID_DEADRISE.Name(), DP::MID_DEADRISE.Value(), 0, 1);
	SideSlope() = std::make_shared<Leg_Model_BndParam>(DP::MID_SIDE_SLOPE.Index(), DP::MID_SIDE_SLOPE.Name(), DP::MID_SIDE_SLOPE.Value(), 0, 1);
}

AutLib::Leg_Nihad2_KeelParams::Leg_Nihad2_KeelParams()
{
	thePosition_ = std::make_shared<Leg_Model_BndParam>(DP::KEEL_POSITION.Index(), DP::KEEL_POSITION.Name(), DP::KEEL_POSITION.Value(), 0, 1);
	theRisePoint_ = std::make_shared<Leg_Model_BndParam>(DP::KEEL_RISE_POINT.Index(), DP::KEEL_RISE_POINT.Name(), DP::KEEL_RISE_POINT.Value(), 0, 1);
	theRiseSlope_ = std::make_shared<Leg_Model_BndParam>(DP::KEEL_RISE_SLOPE.Index(), DP::KEEL_RISE_SLOPE.Name(), DP::KEEL_RISE_SLOPE.Value(), 0, 1);
	theTransomSlope_ = std::make_shared<Leg_Model_BndParam>(DP::KEEL_TRANSOM_SLOPE.Index(), DP::KEEL_TRANSOM_SLOPE.Name(), DP::KEEL_TRANSOM_SLOPE.Value(), 0, 1);
}

AutLib::Leg_Nihad2_StemParams::Leg_Nihad2_StemParams()
{
	theBowRounding_ = std::make_shared<Leg_Model_BndParam>(DP::BOW_ROUNDING.Index(), DP::BOW_ROUNDING.Name(), DP::BOW_ROUNDING.Value(), 0, 1);
	theForeFootShape_ = std::make_shared<Leg_Model_BndParam>(DP::FORE_FOOT_SHAPE.Index(), DP::FORE_FOOT_SHAPE.Name(), DP::FORE_FOOT_SHAPE.Value(), 0, 1);
	theStemRake_ = std::make_shared<Leg_Model_BndParam>(DP::STEM_RAKE.Index(), DP::STEM_RAKE.Name(), DP::STEM_RAKE.Value(), 0, 1);
}

AutLib::Leg_Nihad2_TransomParams::Leg_Nihad2_TransomParams()
{
	theRake_ = std::make_shared<Leg_Model_BndParam>(DP::TRANSOM_RAKE.Index(), DP::TRANSOM_RAKE.Name(), DP::TRANSOM_RAKE.Value(), 0, 1);
	theWidth_ = std::make_shared<Leg_Model_BndParam>(DP::TRANSOM_WIDTH.Index(), DP::TRANSOM_WIDTH.Name(), DP::TRANSOM_WIDTH.Value(), 0, 1);
}

AutLib::Leg_Nihad2_HullParams::Leg_Nihad2_HullParams()
{
	theMaxAreaLocation_ = std::make_shared<Leg_Model_BndParam>(DP::MAX_AREA_LOCATION.Index(), DP::MAX_AREA_LOCATION.Name(), DP::MAX_AREA_LOCATION.Value(), 0, 1);
	theAftFullness_ = std::make_shared<Leg_Model_BndParam>(DP::AFT_FULLNESS.Index(), DP::AFT_FULLNESS.Name(), DP::AFT_FULLNESS.Value(), 0, 1);
	theFwdFullness_ = std::make_shared<Leg_Model_BndParam>(DP::FWD_FULLNESS.Index(), DP::FWD_FULLNESS.Name(), DP::FWD_FULLNESS.Value(), 0, 1);
}

