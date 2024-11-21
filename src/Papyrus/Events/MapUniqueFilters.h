#pragma once

#include "Util/StringUtil.h"

namespace Papyrus::Events
{
  struct AnimationEventEx_Filter
	{
		AnimationEventEx_Filter() = default;
		AnimationEventEx_Filter(const RE::BSFixedString& a_eventName)
		{
			const auto splits = StringUtil::StringSplitToOwned(a_eventName, '.');
			eventName[0] = RE::BSFixedString{ splits.front() };
			eventName[1] = RE::BSFixedString{ splits.size() > 1 ? splits.back() : "" };
			logger::info("Registered Callback for AnimEventEx: {} - Payload: {}", eventName[0].data(), eventName[1].data());
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
} // namespace Paprus::Event
