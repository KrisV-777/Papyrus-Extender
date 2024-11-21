#pragma once

#include "MapUniqueFilters.h"

namespace Papyrus::Events
{
	class EventManager :
		public Singleton<EventManager>
	{
	public:
#define SCRIPTEVENT(NAME, KIND, ...) SKSE::RegistrationMapUnique<NAME##_Filter, __VA_ARGS__> _##NAME{ "On" #NAME };
#include ".defines/EventsMapUnique.def"
#undef SCRIPTEVENT

	public:
		void Save(SKSE::SerializationInterface* a_intfc, std::uint32_t a_version);
		void Load(SKSE::SerializationInterface* a_intfc, std::uint32_t a_type);
		void Revert(SKSE::SerializationInterface* a_intfc);
		void FormDelete(RE::VMHandle a_handle);
	};

}	 // namespace Papyrus::Events
