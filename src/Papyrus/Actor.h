#pragma once

namespace Papyrus::Actor
{
	RE::BSFixedString GetRaceType(STATICARGS, RE::Actor* a_actor);

  void SetActorCalmed(STATICARGS, RE::Actor* a_actor, bool a_calmed);
	void SetActorFrozen(STATICARGS, RE::Actor* a_target, bool a_frozen);
	bool IsActorCalmed(STATICARGS, RE::Actor* a_actor);
	bool IsActorFrozen(STATICARGS, RE::Actor* a_actor);

	std::vector<RE::Actor*> GetDetectedActors(STATICARGS, RE::Actor* a_actor);
	std::vector<RE::Actor*> GetDetectedBy(STATICARGS, RE::Actor* a_actor);

	std::vector<RE::TESObjectARMO*> GetWornForms(STATICARGS, RE::Actor* a_actor, uint32_t a_slotmask);
	std::vector<RE::BGSKeyword*> WornHasKeywords(STATICARGS, RE::Actor* a_actor, std::vector<RE::BGSKeyword*> a_kwds);
  std::vector<RE::BGSKeyword*> WornHasKeywordStrings(STATICARGS, RE::Actor* a_actor, std::vector<RE::BSFixedString> a_kwds, bool a_partialmatch);

	RE::Actor* GetPlayerSpeechTarget(RE::StaticFunctionTag*);
	void Dismount(STATICARGS, RE::Actor* a_actor);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetRaceType, "SPE_Actor", false);

		REGISTERFUNC(SetActorCalmed, "SPE_Actor", false);
		REGISTERFUNC(SetActorFrozen, "SPE_Actor", false);
		REGISTERFUNC(IsActorCalmed, "SPE_Actor", false);
		REGISTERFUNC(IsActorFrozen, "SPE_Actor", false);

		REGISTERFUNC(GetDetectedActors, "SPE_Actor", false);
		REGISTERFUNC(GetDetectedBy, "SPE_Actor", false);

		REGISTERFUNC(GetWornForms, "SPE_Actor", false);
		REGISTERFUNC(WornHasKeywords, "SPE_Actor", false);
		REGISTERFUNC(WornHasKeywordStrings, "SPE_Actor", false);

		REGISTERFUNC(GetPlayerSpeechTarget, "SPE_Actor", false);
		REGISTERFUNC(Dismount, "SPE_Actor", true);

		return true;
	};

} // namespace Papyrus::Actor
