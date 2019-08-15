#include <constantsSwitch.hxx>

namespace AutLib
{
	namespace debug
	{
		// Hashtables to static class attributes addresses holding the
		// runtime constantsSwitch values.
		// This needs to go on the heap so the destructor will not get
		//  called before the objects' destructor it is overseeing
		ListConstantsControlSwitches* constantsSwitchValues_(NULL);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	}
}