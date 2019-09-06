#include <SizeMap2d_FullIntAnIsoInfo.hxx>

//#include <Mesh_Info.hxx>

const Standard_Integer AutLib::SizeMap2d_FullIntAnIsoInfo::DEFAULT_NB_SAMPLES(3);

AutLib::SizeMap2d_FullIntAnIsoInfo::SizeMap2d_FullIntAnIsoInfo()
	: theNbSamples_(DEFAULT_NB_SAMPLES)
{
	/*theIterCorrInfo_ = mesh_size_map2d_full_aniso_optm_point_iter_correct_info;
	theAdaptIntgInfo_ = mesh_size_map2d_full_aniso_adapt_integration_info;*/
}