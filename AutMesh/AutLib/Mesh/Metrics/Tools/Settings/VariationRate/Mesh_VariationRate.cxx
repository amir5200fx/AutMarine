#include <Mesh_VariationRate.hxx>

Standard_Real AutLib::Mesh_VariationRate::Rate(const Mesh_VariationRateInfo Info)
{
	switch (Info)
	{
	case Mesh_VariationRateInfo_VerySLOW:
		return VeryLowrate();
	case Mesh_VariationRateInfo_SLOW:
		return Lowrate();
	case Mesh_VariationRateInfo_MODERATE:
		return Moderate();
	case Mesh_VariationRateInfo_FAST:
		return Highrate();
	}

	return Custom();
}