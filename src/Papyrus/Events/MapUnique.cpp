#include "MapUnique.h"

namespace Papyrus::Events::MapUnique
{
#define REGISTER(type, match, ...)                                                                 \
	if (!obj) {                                                                                      \
		a_vm->TraceStack("obj is none", a_stackID);                                                    \
		return;                                                                                        \
	}                                                                                                \
	EventManager::GetSingleton()->type.Register(obj, AnimationEventEx_Filter{ __VA_ARGS__ }, match); \
	RegisterImpl(obj);
#define UNREGISTER(type, match, ...)                                                                 \
	if (!obj) {                                                                                        \
		a_vm->TraceStack("obj is none", a_stackID);                                                      \
		return;                                                                                          \
	}                                                                                                  \
	EventManager::GetSingleton()->type.Unregister(obj, AnimationEventEx_Filter{ __VA_ARGS__ }, match); \
	UnregisterImpl(obj);

  void AnimationEventEx::RegisterForAnimationEventEx(STATICARGS, RE::Actor* obj, RE::BSFixedString filter) { REGISTER(_AnimationEventEx, true, filter); }
  void AnimationEventEx::RegisterForAnimationEventEx_Alias(STATICARGS, RE::BGSRefAlias* obj, RE::BSFixedString filter) { REGISTER(_AnimationEventEx, true, filter); }
  void AnimationEventEx::RegisterForAnimationEventEx_MgEff(STATICARGS, RE::ActiveEffect* obj, RE::BSFixedString filter) { REGISTER(_AnimationEventEx, true, filter); }
  void AnimationEventEx::UnregisterForAnimationEventEx(STATICARGS, RE::Actor* obj, RE::BSFixedString filter) { UNREGISTER(_AnimationEventEx, true, filter); }
  void AnimationEventEx::UnregisterForAnimationEventEx_Alias(STATICARGS, RE::BGSRefAlias* obj, RE::BSFixedString filter) { UNREGISTER(_AnimationEventEx, true, filter); }
  void AnimationEventEx::UnregisterForAnimationEventEx_MgEff(STATICARGS, RE::ActiveEffect* obj, RE::BSFixedString filter) { UNREGISTER(_AnimationEventEx, true, filter); }

	void AnimationEventEx::RegisterImpl(const RE::Actor* a_ref)
	{
		a_ref->AddAnimationGraphEventSink(GetSingleton());
	}
	void AnimationEventEx::UnregisterImpl(const RE::Actor* a_ref)
	{
		a_ref->RemoveAnimationGraphEventSink(GetSingleton());
	}
	void AnimationEventEx::RegisterImpl(const RE::ActiveEffect* a_ref)	{
		if (const auto ref = a_ref->GetTargetActor())
			ref->AddAnimationGraphEventSink(GetSingleton());
	}
	void AnimationEventEx::UnregisterImpl(const RE::ActiveEffect* a_ref)	{
		if (const auto ref = a_ref->GetTargetActor())
			ref->RemoveAnimationGraphEventSink(GetSingleton());
	}
	void AnimationEventEx::RegisterImpl(const RE::BGSRefAlias* a_ref)	{
		if (const auto ref = a_ref->GetActorReference())
			ref->AddAnimationGraphEventSink(GetSingleton());
	}
	void AnimationEventEx::UnregisterImpl(const RE::BGSRefAlias* a_ref)	{
		if (const auto ref = a_ref->GetActorReference())
			ref->RemoveAnimationGraphEventSink(GetSingleton());
	}
} // namespace Papyrus::Events
