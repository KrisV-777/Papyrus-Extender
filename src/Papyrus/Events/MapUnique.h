#pragma once

#include "EventManager.h"
#include "Util/StringUtil.h"

namespace Papyrus::Events::MapUnique
{
#define REGISTER(type, match, ...)                                                                  \
	if (!obj) {                                                                                       \
		a_vm->TraceStack("obj is none", a_stackID);                                                     \
		return;                                                                                         \
	}                                                                                                 \
	EventManager::GetSingleton()->type.Register(obj, AnimationEventEx_Filter{ __VA_ARGS__ }, match); \
	RegisterImpl(obj);
#define UNREGISTER(type, match, ...)                                                                  \
	if (!obj) {                                                                                         \
		a_vm->TraceStack("obj is none", a_stackID);                                                       \
		return;                                                                                           \
	}                                                                                                   \
	EventManager::GetSingleton()->type.Unregister(obj, AnimationEventEx_Filter{ __VA_ARGS__ }, match); \
	UnregisterImpl(obj);

	struct AnimationEventEx :
		public Singleton<AnimationEventEx>,
		public RE::BSTEventSink<RE::BSAnimationGraphEvent>
	{
		static inline void RegisterForAnimationEventEx(STATICARGS, RE::Actor* obj, RE::BSFixedString filter) { REGISTER(_AnimationEventEx, true, filter); }
		static inline void RegisterForAnimationEventEx_Alias(STATICARGS, RE::BGSRefAlias* obj, RE::BSFixedString filter) { REGISTER(_AnimationEventEx, true, filter); }
		static inline void RegisterForAnimationEventEx_MgEff(STATICARGS, RE::ActiveEffect* obj, RE::BSFixedString filter) { REGISTER(_AnimationEventEx, true, filter); }
		static inline void UnregisterForAnimationEventEx(STATICARGS, RE::Actor* obj, RE::BSFixedString filter) { UNREGISTER(_AnimationEventEx, true, filter); }
		static inline void UnregisterForAnimationEventEx_Alias(STATICARGS, RE::BGSRefAlias* obj, RE::BSFixedString filter) { UNREGISTER(_AnimationEventEx, true, filter); }
		static inline void UnregisterForAnimationEventEx_MgEff(STATICARGS, RE::ActiveEffect* obj, RE::BSFixedString filter) { UNREGISTER(_AnimationEventEx, true, filter); }

	protected:
		using EventResult = RE::BSEventNotifyControl;
		EventResult ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>*) override
		{
			if (!a_event || a_event->holder->IsNot(RE::FormType::ActorCharacter)) {
				return EventResult::kContinue;
			}
			auto source = const_cast<RE::Actor*>(a_event->holder->As<RE::Actor>());
			assert(source);
			Papyrus::Events::EventManager::GetSingleton()->_AnimationEventEx.QueueEvent(
					source,
					[=](const AnimationEventEx_Filter& a_filter, bool a_match) {	 //capture by reference [&] bad
						return a_match == a_filter.Apply(a_event->tag, a_event->payload);
					},
					source, a_event->tag, a_event->payload);

			return EventResult::kContinue;
		}

	private:
		static inline void RegisterImpl(const RE::Actor* a_ref) { a_ref->AddAnimationGraphEventSink(GetSingleton()); }
		static inline void UnregisterImpl(const RE::Actor* a_ref) { a_ref->RemoveAnimationGraphEventSink(GetSingleton()); }
		static inline void RegisterImpl(const RE::ActiveEffect* a_ref)
		{
			if (const auto ref = a_ref->GetTargetActor())
				ref->AddAnimationGraphEventSink(GetSingleton());
		}
		static inline void UnregisterImpl(const RE::ActiveEffect* a_ref)
		{
			if (const auto ref = a_ref->GetTargetActor())
				ref->RemoveAnimationGraphEventSink(GetSingleton());
		}
		static inline void RegisterImpl(const RE::BGSRefAlias* a_ref)
		{
			if (const auto ref = a_ref->GetActorReference())
				ref->AddAnimationGraphEventSink(GetSingleton());
		}
		static inline void UnregisterImpl(const RE::BGSRefAlias* a_ref)
		{
			if (const auto ref = a_ref->GetActorReference())
				ref->RemoveAnimationGraphEventSink(GetSingleton());
		}

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
