#include "EventManager.h"

namespace Papyrus::Events
{
	void EventManager::Save(SKSE::SerializationInterface* a_intfc, std::uint32_t a_version)
	{
#define SCRIPTEVENT(NAME, KIND, ...) _##NAME.Save(a_intfc, KIND, a_version);
#include ".defines/EventsMapUnique.def"
#undef SCRIPTEVENT
	}

	void EventManager::Load(SKSE::SerializationInterface* a_intfc, std::uint32_t a_type)
	{
		switch (a_type) {
#define SCRIPTEVENT(NAME, KIND, ...) \
	case KIND:                         \
		_##NAME.Load(a_intfc);           \
		break;
#include ".defines/EventsMapUnique.def"

		default:
			logger::warn("Unknown Type: {}", Serialization::GetTypeName(a_type));
			break;
#undef SCRIPTEVENT
		}
	}

	void EventManager::Revert(SKSE::SerializationInterface* a_intfc)
	{
#define SCRIPTEVENT(NAME, KIND, ...) _##NAME.Revert(a_intfc);
#include ".defines/EventsMapUnique.def"
#undef SCRIPTEVENT
	}

	void EventManager::FormDelete(RE::VMHandle a_handle)
	{
#define SCRIPTEVENT(NAME, KIND, ...) _##NAME.UnregisterAll(a_handle);
#include ".defines/EventsMapUnique.def"
#undef SCRIPTEVENT
	}

}	 // namespace Papyrus::Events