#pragma once

// #include "MapUnique.h"
#include "Util/StringUtil.h"

namespace Papyrus::Events
{
	struct AnimationEventEx_Filter
	{
		AnimationEventEx_Filter() = default;
		AnimationEventEx_Filter(const RE::BSFixedString& a_eventName)
		{
			const auto splits = StringUtil::StringSplit(a_eventName, '.');
			eventName[0] = splits.front();
			eventName[1] = splits.size() > 1 ? splits.back() : "";
		}
		~AnimationEventEx_Filter() = default;

		bool Apply(const RE::BSFixedString& a_event, const RE::BSFixedString& a_payload) const
		{
			return a_event == eventName[0] && (eventName[1].empty() || a_payload == eventName[1]);
		}
		bool Load(SKSE::SerializationInterface* a_intfc)
		{
			std::string out;
			const auto read = [&](const size_t idx) -> bool {
				if (stl::read_string(a_intfc, out)) {
					eventName[idx] = out;
					return true;
				}
				return false;
			};
			return read(0) && read(1);
		}
		bool Save(SKSE::SerializationInterface* a_intfc) const
		{
			return stl::write_string(a_intfc, eventName[0]) && stl::write_string(a_intfc, eventName[1]);
		}

		bool operator<(const AnimationEventEx_Filter& a_rhs) const
		{
			using svpair = std::pair<std::string_view, std::string_view>;
			return svpair(eventName[0], eventName[1]) < svpair(a_rhs.eventName[0], a_rhs.eventName[1]);
		}

		RE::BSFixedString eventName[2];
	};

	class EventManager :
		public Singleton<EventManager>
	{
	public:
#define SCRIPTEVENT(NAME, KIND, ...) SKSE::RegistrationMapUnique<AnimationEventEx_Filter, __VA_ARGS__> _##NAME{ "On" #NAME };
		SCRIPTEVENT(AnimationEventEx, 'aevx', const RE::TESObjectREFR*, RE::BSFixedString, RE::BSFixedString)
// #include ".defines/EventsMapUnique.def"
#undef SCRIPTEVENT

	public:
		void Save(SKSE::SerializationInterface* a_intfc, std::uint32_t a_version);
		void Load(SKSE::SerializationInterface* a_intfc, std::uint32_t a_type);
		void Revert(SKSE::SerializationInterface* a_intfc);
		void FormDelete(RE::VMHandle a_handle);
	};

}	 // namespace Papyrus::Events