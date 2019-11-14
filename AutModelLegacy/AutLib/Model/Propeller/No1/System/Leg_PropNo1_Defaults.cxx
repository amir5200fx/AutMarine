#include <Leg_PropNo1_Defaults.hxx>

namespace AutLib
{

	const Standard_Integer Leg_PropNo1_Defaults::NB_BLADES(5);
	const Standard_Integer Leg_PropNo1_Defaults::NB_SECTIONS(24);
	const Standard_Integer Leg_PropNo1_Defaults::NB_SPANS(20);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::DIAMETER(1, "diameter", 300 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::HUB_RADIUS(2, "hubRadius", 30 * 0.02);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::HUB_LENGTH(3, "hubLength", 70.0*0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::HUB_WEIGHT(4, "hubWeight", 0.5);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::SHAFT_LENGTH(5, "shaftLength", 2400 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::SHAFT_OFFSET(6, "shaftOffset", 50 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::SHAFT_RADIUS(7, "shaftRadius", 15 * 0.02);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::PITCH_ROOT(8, "pitchRoot", 55);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::PITCH_TIP(9, "pitchTip", 25);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::PITCH_ROOT_STEEP(10, "pitchRootSteep", 0.5);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::PITCH_TIP_STEEP(11, "pitchTipSteep", 0.8);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::SKEW_ROOT_STEEP(12, "skewRootSteep", 0.5);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::SKEW_TIP(13, "skewTip", 100 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::SKEW_TIP_STEEP(14, "skewTipSteep", 0.5);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CHORD_MAX_LOCATION(15, "chordMaxLoc", 0.6);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CHORD_MAX(16, "chordMax", 80 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CHORD_ROOT(17, "chordRoot", 20 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CHORD_ROOT_WEIGHT(18, "chordRootWeight", 0.5);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CHORD_TIP(19, "chordTip", 0);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CHORD_TIP_WEIGHT(20, "chordTipWeight", 0.8);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CAMBER_MAX_LOCATION(21, "camberMaxLoc", 0.5);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CAMBER_MAX(22, "camberMax", 0.01);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CAMBER_ROOT(23, "camberRoot", 0.004);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CAMBER_ROOT_WEIGHT(24, "camberRootWeight", 0.5);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CAMBER_TIP(25, "camberTip", 0);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::CAMBER_TIP_WEIGHT(26, "camberTipWeight", 0.5);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::THICK_ROOT(27, "thickRoot", 6 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::THICK_TIP(28, "thickTip", 3 * 0.02);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::THICK_ROOT_STEEP(29, "thickRootSteep", 0.5);
	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::THICK_TIP_STEEP(30, "thickTipSteep", 0.5);

	const Leg_PropNo1_Defaults::param Leg_PropNo1_Defaults::RAKE(31, "rake", 30 * 0.02);
}