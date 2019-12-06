#include <CadSingularity_Detection_System.hxx>

#include <CadSingularity_Detection_Info.hxx>

std::shared_ptr<AutLib::CadSingularity_Detection_Info> 
AutLib::cadSingularSys::gl_singularity_detection_info = std::make_shared<AutLib::CadSingularity_Detection_Info>();