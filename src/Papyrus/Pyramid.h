#pragma once

namespace Papyrus::Pyramid
{
  bool HasKeywords(RE::TESForm* a_form, std::vector<RE::BGSKeyword*> a_kwds, bool a_matchAll);
  void SetActorCalmed(RE::StaticFunctionTag*, RE::Actor* a_actor, bool a_calmed);
  void SetActorFrozen(RE::StaticFunctionTag*, RE::Actor* a_target, bool a_frozen);
  std::vector<RE::Actor*> GetDetectedBy(RE::StaticFunctionTag*, RE::Actor* a_target);
  std::vector<RE::BGSKeyword*> WornHasKeywords(RE::StaticFunctionTag*, RE::Actor* a_actor, std::vector<RE::BGSKeyword*> a_kwds);
  std::vector<RE::BGSKeyword*> WornHasKeywordStrings(RE::StaticFunctionTag*, RE::Actor* a_actor, std::vector<std::string> a_kwds);
  std::vector<RE::TESForm*> GetItemsByKeyword(RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall);
  std::vector<RE::TESForm*> FilterFormsByKeyword(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall, bool a_invert);
  std::vector<RE::TESForm*> FilterFormsByGoldValue(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, int a_value, bool a_greater, bool a_equal);
  std::vector<RE::TESForm*> FilterByEnchanted(RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, std::vector<RE::TESForm*> a_forms, bool a_ench);
	std::vector<RE::TESForm*> FilterByEquippedSlot(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, std::vector<int> a_slots, bool a_all);
	RE::TESGlobal* GetGlobal(RE::StaticFunctionTag*, std::string a_edid);
	bool FormHasKeyword(RE::StaticFunctionTag*, RE::TESForm* a_form, std::vector<RE::BGSKeyword*> a_kwds, bool a_all);
  bool FormHasKeywordStrings(RE::StaticFunctionTag*, RE::TESForm* a_form, std::vector<std::string> a_kwds, bool a_all);
  long RemoveForms(RE::StaticFunctionTag*, RE::TESObjectREFR* a_fromContainer, std::vector<RE::TESForm*> a_forms, RE::TESObjectREFR* a_toContainer);
  RE::Actor* GetPlayerSpeechTarget(RE::StaticFunctionTag*);
  std::string GetButtonForDXScanCode(RE::StaticFunctionTag*, int a_keyCode);
  std::string ReplaceAt(RE::StaticFunctionTag*, std::string a_str, int a_index, std::string a_replacement);
  RE::TESObjectREFR* GetQuestMarker(RE::StaticFunctionTag*, RE::TESQuest* a_quest);
  std::vector<RE::TESWorldSpace*> GetExteriorWorldSpaces(RE::StaticFunctionTag*, RE::TESObjectCELL* a_cell);
  std::vector<RE::BGSLocation*> GetExteriorLocations(RE::StaticFunctionTag*, RE::TESObjectCELL* a_cell);
  std::vector<RE::TESForm*> GetInventoryNamedObjects(RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, std::vector<std::string> itemNames);
  void Dismount(RE::StaticFunctionTag*, RE::Actor* a_actor);
  float GetTemperFactor(RE::StaticFunctionTag*, RE::TESObjectREFR* a_container, RE::TESForm* a_form);
  float GetTravelDistance(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref1, RE::TESObjectREFR* a_ref2);
  float GetAbsPosX(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);
  float GetAbsPosY(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);
  float GetAbsPosZ(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);

	inline bool Register(VM* a_vm)
	{
		// actors
		REGISTERFUNC(SetActorCalmed, "PyramidUtils", true);
		REGISTERFUNC(SetActorFrozen, "PyramidUtils", true);
		REGISTERFUNC(GetDetectedBy, "PyramidUtils", true);
		REGISTERFUNC(WornHasKeywords, "PyramidUtils", true);
		REGISTERFUNC(WornHasKeywordStrings, "PyramidUtils", true);

		// inv processing
		REGISTERFUNC(GetItemsByKeyword, "PyramidUtils", true);
		REGISTERFUNC(FilterFormsByKeyword, "PyramidUtils", true);
		REGISTERFUNC(FilterFormsByGoldValue, "PyramidUtils", true);
		REGISTERFUNC(FilterByEnchanted, "PyramidUtils", true);
		REGISTERFUNC(RemoveForms, "PyramidUtils", true);
		REGISTERFUNC(GetInventoryNamedObjects, "PyramidUtils", true);
		REGISTERFUNC(GetTemperFactor, "PyramidUtils", true);
		REGISTERFUNC(FilterByEquippedSlot, "PyramidUtils", true);

		// forms
		REGISTERFUNC(FormHasKeyword, "PyramidUtils", true);
		REGISTERFUNC(FormHasKeywordStrings, "PyramidUtils", true);

		// player
		REGISTERFUNC(GetPlayerSpeechTarget, "PyramidUtils", true);
		REGISTERFUNC(Dismount, "PyramidUtils", true);

		// input
		REGISTERFUNC(GetButtonForDXScanCode, "PyramidUtils", true);

		// strings
		REGISTERFUNC(ReplaceAt, "PyramidUtils", true);

		// geography
		REGISTERFUNC(GetQuestMarker, "PyramidUtils", true);
		REGISTERFUNC(GetExteriorWorldSpaces, "PyramidUtils", true);
		REGISTERFUNC(GetExteriorLocations, "PyramidUtils", true);
		REGISTERFUNC(GetTravelDistance, "PyramidUtils", true);
		REGISTERFUNC(GetAbsPosX, "PyramidUtils", true);
		REGISTERFUNC(GetAbsPosY, "PyramidUtils", true);
		REGISTERFUNC(GetAbsPosZ, "PyramidUtils", true);

		// misc
		REGISTERFUNC(GetGlobal, "PyramidUtils", true);

		return true;
	}
} // namespace Papyrus::Pyramid
