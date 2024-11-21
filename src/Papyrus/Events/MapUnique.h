#pragma once

#include "EventManager.h"
#include "MapUniqueFilters.h"

namespace Papyrus::Events::MapUnique
{
	struct AnimationEventEx :
		public Singleton<AnimationEventEx>,
		public RE::BSTEventSink<RE::BSAnimationGraphEvent>
	{
		static void RegisterForAnimationEventEx(STATICARGS, RE::Actor* obj, RE::BSFixedString filter);
		static void RegisterForAnimationEventEx_Alias(STATICARGS, RE::BGSRefAlias* obj, RE::BSFixedString filter);
		static void RegisterForAnimationEventEx_MgEff(STATICARGS, RE::ActiveEffect* obj, RE::BSFixedString filter);
		static void UnregisterForAnimationEventEx(STATICARGS, RE::Actor* obj, RE::BSFixedString filter);
		static void UnregisterForAnimationEventEx_Alias(STATICARGS, RE::BGSRefAlias* obj, RE::BSFixedString filter);
		static void UnregisterForAnimationEventEx_MgEff(STATICARGS, RE::ActiveEffect* obj, RE::BSFixedString filter);

	protected:
		using EventResult = RE::BSEventNotifyControl;
		EventResult ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>*) override
		{
			if (!a_event || a_event->holder->IsNot(RE::FormType::ActorCharacter)) {
				return EventResult::kContinue;
			}
			const auto source = const_cast<RE::Actor*>(a_event->holder->As<RE::Actor>());
			const auto &tag = a_event->tag, &payload = a_event->payload;
			assert(source);
			Papyrus::Events::EventManager::GetSingleton()->_AnimationEventEx.QueueEvent(
					source,
					[=](const AnimationEventEx_Filter& a_filter, bool a_match) {
						return a_match == a_filter.Apply(tag, payload);
					},
					source, tag, payload);

			return EventResult::kContinue;
		}

	private:
		static void RegisterImpl(const RE::Actor* a_ref);
		static void UnregisterImpl(const RE::Actor* a_ref);
		static void RegisterImpl(const RE::ActiveEffect* a_ref);
		static void UnregisterImpl(const RE::ActiveEffect* a_ref);
		static void RegisterImpl(const RE::BGSRefAlias* a_ref);
		static void UnregisterImpl(const RE::BGSRefAlias* a_ref);

	public:
		static inline void Register(VM* a_vm)
		{
			REGISTERFUNC(RegisterForAnimationEventEx, "SPE_Events", true);
			REGISTERFUNC(RegisterForAnimationEventEx_Alias, "SPE_Events", true);
			REGISTERFUNC(RegisterForAnimationEventEx_MgEff, "SPE_Events", true);
			REGISTERFUNC(UnregisterForAnimationEventEx, "SPE_Events", true);
			REGISTERFUNC(UnregisterForAnimationEventEx_Alias, "SPE_Events", true);
			REGISTERFUNC(UnregisterForAnimationEventEx_MgEff, "SPE_Events", true);

			logger::info("Initialized AnimationEventEx"sv);
		}
	};

	inline bool Register(VM* a_vm)
	{
		AnimationEventEx::GetSingleton()->Register(a_vm);
		return true;
	}

}	 // namespace Papyrus::Events
