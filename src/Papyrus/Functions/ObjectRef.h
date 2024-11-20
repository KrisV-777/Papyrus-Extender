#pragma once

namespace Papyrus::ObjectRef
{
	std::vector<RE::TESForm*> GetEnchantedItems(STATICARGS, RE::TESObjectREFR* a_ref, bool a_weapons, bool a_armors, bool a_wornonly);
	std::vector<RE::TESForm*> GetInventoryNamedObjects(STATICARGS, RE::TESObjectREFR* a_ref, std::vector<RE::BSFixedString> itemNames);
	std::vector<RE::TESForm*> GetItemsByKeyword(STATICARGS, RE::TESObjectREFR* a_ref, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall);
	int32_t RemoveItems(STATICARGS, RE::TESObjectREFR* a_reference, std::vector<RE::TESForm*> a_forms, RE::TESObjectREFR* a_target);

	float GetTemperFactor(STATICARGS, RE::TESObjectREFR* a_reference, RE::TESForm* a_form);

  float GetTravelDistance(STATICARGS, RE::TESObjectREFR* a_ref1, RE::TESObjectREFR* a_ref2);
  float GetAbsPosX(STATICARGS, RE::TESObjectREFR* a_ref);
  float GetAbsPosY(STATICARGS, RE::TESObjectREFR* a_ref);
  float GetAbsPosZ(STATICARGS, RE::TESObjectREFR* a_ref);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetEnchantedItems, "SPE_ObjectRef", true);
		REGISTERFUNC(GetInventoryNamedObjects, "SPE_ObjectRef", true);
		REGISTERFUNC(GetItemsByKeyword, "SPE_ObjectRef", true);
		REGISTERFUNC(RemoveItems, "SPE_ObjectRef", true);

		REGISTERFUNC(GetTemperFactor, "SPE_ObjectRef", true);

		REGISTERFUNC(GetTravelDistance, "SPE_ObjectRef", true);
		REGISTERFUNC(GetAbsPosX, "SPE_ObjectRef", true);
		REGISTERFUNC(GetAbsPosY, "SPE_ObjectRef", true);
		REGISTERFUNC(GetAbsPosZ, "SPE_ObjectRef", true);

		return true;
	}
} // namespace Papyrus::ObjectRef
