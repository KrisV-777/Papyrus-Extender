#include "Papyrus.h"

#include "Actor.h"
#include "Cell.h"
#include "Form.h"
#include "GlobalVariable.h"
#include "Interface.h"
#include "Location.h"
#include "ObjectRef.h"
#include "PyramidUtils.h"
#include "Quest.h"
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
		papyrus->Register(Cell::Register);
		papyrus->Register(Form::Register);
		papyrus->Register(GlobalVariable::Register);
		papyrus->Register(Interface::Register);
		papyrus->Register(Location::Register);
		papyrus->Register(ObjectRef::Register);
		papyrus->Register(Quest::Register);
		papyrus->Register(Util::Register);

		papyrus->Register(PyramidUtilsP::Register);

		logger::info("Registered Papyrus Functions");

		return true;
	}
}	 // namespace Papyrus