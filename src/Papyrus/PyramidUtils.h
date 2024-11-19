#pragma once

namespace Papyrus::PyramidUtilsP
{
	// COMEBACK: Idk where to sort this in. Mayhaps split it up into different functions?
  std::vector<RE::TESForm*> FilterByEnchanted(STATICARGS, RE::TESObjectREFR* a_container, std::vector<RE::TESForm*> a_forms, bool a_ench);

  std::vector<RE::TESWorldSpace*> GetExteriorWorldSpaces(STATICARGS, RE::TESObjectCELL* a_cell);
  std::vector<RE::BGSLocation*> GetExteriorLocations(STATICARGS, RE::TESObjectCELL* a_cell);
  std::vector<RE::TESForm*> GetInventoryNamedObjects(STATICARGS, RE::TESObjectREFR* a_container, std::vector<std::string> itemNames);

	std::vector<RE::TESForm*> GetItemsByKeyword(STATICARGS, RE::TESObjectREFR* a_container, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall);
	long RemoveForms(STATICARGS, RE::TESObjectREFR* a_fromContainer, std::vector<RE::TESForm*> a_forms, RE::TESObjectREFR* a_toContainer);
	float GetTemperFactor(STATICARGS, RE::TESObjectREFR* a_container, RE::TESForm* a_form);
  float GetTravelDistance(STATICARGS, RE::TESObjectREFR* a_ref1, RE::TESObjectREFR* a_ref2);
  float GetAbsPosX(STATICARGS, RE::TESObjectREFR* a_ref);
  float GetAbsPosY(STATICARGS, RE::TESObjectREFR* a_ref);
  float GetAbsPosZ(STATICARGS, RE::TESObjectREFR* a_ref);

	inline bool Register(VM* a_vm)
	{
		// inv processing
		REGISTERFUNC(GetItemsByKeyword, "PyramidUtils", true);
		REGISTERFUNC(FilterByEnchanted, "PyramidUtils", true);
		REGISTERFUNC(RemoveForms, "PyramidUtils", true);
		REGISTERFUNC(GetInventoryNamedObjects, "PyramidUtils", true);
		REGISTERFUNC(GetTemperFactor, "PyramidUtils", true);

		// geography
		REGISTERFUNC(GetQuestMarker, "PyramidUtils", true);
		REGISTERFUNC(GetExteriorWorldSpaces, "PyramidUtils", true);
		REGISTERFUNC(GetExteriorLocations, "PyramidUtils", true);
		REGISTERFUNC(GetTravelDistance, "PyramidUtils", true);
		REGISTERFUNC(GetAbsPosX, "PyramidUtils", true);
		REGISTERFUNC(GetAbsPosY, "PyramidUtils", true);
		REGISTERFUNC(GetAbsPosZ, "PyramidUtils", true);

		return true;
	}
}	 // namespace Papyrus
