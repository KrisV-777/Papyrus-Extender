#include "Papyrus.h"

#include "Actor.h"
#include "Interface.h"
#include "Utility.h"

namespace Papyrus
{
	bool Register()
	{
		const auto papyrus = SKSE::GetPapyrusInterface();
		if (!papyrus) {
			logger::critical("Failed to get papyurs interface");
			return false;
		}

		papyrus->Register(Actor::Register);
    papyrus->Register(Interface::Register);
    papyrus->Register(Utility::Register);

    return true;
	}
}	 // namespace Papyrus