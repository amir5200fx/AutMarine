#include <Marine_WaveProfile.hxx>

AutLib::Marine_WaveProfile::Marine_WaveProfile
(
	const Standard_Real theTa, 
	const Standard_Real theTf
)
	: theTa_(theTa)
	, theTf_(theTf)
	, theTm_(MEAN(theTa, theTf))
	, Global_Bound<Standard_Real>(0, 1)
{}

AutLib::Marine_WaveProfile::Marine_WaveProfile
(
	const Standard_Real theTa,
	const Standard_Real theTf,
	const Standard_Real theTm
)
	: theTa_(theTa)
	, theTf_(theTf)
	, theTm_(theTm)
	, Global_Bound<Standard_Real>(0, 1)
{}