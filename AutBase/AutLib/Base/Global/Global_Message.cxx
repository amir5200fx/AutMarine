#include <Global_Message.hxx>

std::shared_ptr<AutLib::Global_Message> 
AutLib::gl_messenger = std::make_shared<AutLib::Global_MessageOstream>();