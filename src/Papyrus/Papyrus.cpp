#include "Papyrus.h"

#include "Events/MapUnique.h"
#include "Functions/Actor.h"
#include "Functions/Cell.h"
#include "Functions/Form.h"
#include "Functions/GlobalVariable.h"
#include "Functions/Interface.h"
#include "Functions/Location.h"
#include "Functions/ObjectRef.h"
#include "Functions/Quest.h"
#include "Functions/Utility.h"

namespace Papyrus
{
	bool Register()
	{
		const auto papyrus = SKSE::GetPapyrusInterface();
		if (!papyrus) {
			logger::critical("Failed to get papyurs interface");
			return false;
		}

		papyrus->Register(Events::MapUnique::Register);

		papyrus->Register(Actor::Register);
		papyrus->Register(Cell::Register);
		papyrus->Register(Form::Register);
		papyrus->Register(GlobalVariable::Register);
		papyrus->Register(Interface::Register);
		papyrus->Register(Location::Register);
		papyrus->Register(ObjectRef::Register);
		papyrus->Register(Quest::Register);
		papyrus->Register(Utility::Register);

		logger::info("Registered Papyrus Functions");

		return true;
	}
}	 // namespace Papyrus