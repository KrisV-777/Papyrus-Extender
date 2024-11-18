#include "PyramidUtils.h"

#include "PyramidUtils/Geography.h"
#include "PyramidUtils/Input.h"
#include "PyramidUtils/MarkerManager.h"
#include "Utility/StringUtil.h"
#include "Utility/Keywords.h"

namespace Papyrus::PyramidUtilsP
{
	std::vector<RE::TESForm*> GetItemsByKeyword(STATICARGS, RE::TESObjectREFR* a_container, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall)
	{
    if (!a_container) {
      TRACESTACK("GetItemsByKeyword: container is nullptr");
      return std::vector<RE::TESForm*>{};
    }
		std::vector<RE::TESForm*> filtered{};
		auto inventory = a_container->GetInventory();
		for (const auto& [form, data] : inventory) {
			if (!form->GetPlayable() || form->GetName()[0] == '\0')
				continue;
			if (a_keywords.empty() || Utility::HasKeywords(form, a_keywords, a_matchall)) {
				filtered.push_back(form);
			}
		}
		return filtered;
	}

	std::vector<RE::TESForm*> FilterFormsByKeyword(STATICARGS, std::vector<RE::TESForm*> a_forms, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall, bool a_invert)
	{
		std::vector<RE::TESForm*> filtered;
		for (const auto& form : a_forms) {
      if (!form) {
        TRACESTACK("FilterFormsByKeyword: nullptr in forms");
        break;
      }
			if (Utility::HasKeywords(form, a_keywords, a_matchall) != a_invert) {
				filtered.push_back(form);
			}
		}
		return filtered;
	}

	std::vector<RE::TESForm*> FilterFormsByGoldValue(STATICARGS, std::vector<RE::TESForm*> a_forms, int a_value, bool a_greater, bool a_equal)
	{
		std::vector<RE::TESForm*> filtered;
		for (const auto& form : a_forms) {
      if (!form) {
        TRACESTACK("FilterFormsByGoldValue: nullptr in forms");
        break;
      }
			if ((a_greater && form->GetGoldValue() > a_value) || (!a_greater && form->GetGoldValue() < a_value) || (a_equal && form->GetGoldValue() == a_value)) {
				filtered.push_back(form);
			}
		}
		return filtered;
	}

	std::vector<RE::TESForm*> FilterByEnchanted(STATICARGS, RE::TESObjectREFR* a_container, std::vector<RE::TESForm*> a_forms, bool a_ench)
	{
    if (!a_container) {
      TRACESTACK("FilterByEnchanted: container is nullptr");
      return std::vector<RE::TESForm*>{};
    }
		std::vector<RE::TESForm*> filtered;
		std::unordered_set<RE::TESForm*> forms(a_forms.begin(), a_forms.end());
		auto inventory = a_container->GetInventory();
		for (const auto& [form, data] : inventory) {
			if (!form->GetPlayable() || form->GetName()[0] == '\0')
				continue;
			if ((data.second->GetEnchantment() != nullptr) == a_ench && forms.contains(form)) {
				filtered.push_back(form);
			}
		}
		return filtered;
	}

	std::vector<RE::TESForm*> FilterByEquippedSlot(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, std::vector<int> a_slots, bool a_all)
	{
    // FIXME: Nua mentioned this one to break
		logger::info("FilterByEquippedSlot");
		std::vector<RE::TESForm*> filtered;

		std::vector<RE::BGSBipedObjectForm::BipedObjectSlot> slots;

		for (const auto& slot : a_slots) {
			slots.push_back(static_cast<RE::BGSBipedObjectForm::BipedObjectSlot>(slot));
		}

		for (const auto& form : a_forms) {
			if (const auto& armor = form->As<RE::TESObjectARMO>()) {
				bool include = a_all;
				for (const auto& slot : slots) {
					if (armor->HasPartOf(slot)) {
						if (!a_all) {
							include = true;
							break;
						}
					} else if (a_all) {
						include = false;
						break;
					}
				}

				if (include) {
					filtered.push_back(armor);
				}
			}
		}

		return filtered;
	}

	bool FormHasKeyword(STATICARGS, RE::TESForm* a_form, std::vector<RE::BGSKeyword*> a_kwds, bool a_all)
	{
    if (!a_form) {
      TRACESTACK("FormHasKeyword: form is nullptr");
      return false;
    }
		return Utility::HasKeywords(a_form, a_kwds, a_all);
	}

	bool FormHasKeywordStrings(STATICARGS, RE::TESForm* a_form, std::vector<std::string> a_kwds, bool a_all)
	{
    if (!a_form) {
      TRACESTACK("FormHasKeywordStrings: form is nullptr");
      return false;
    }
		std::vector<RE::BGSKeyword*> kwds;
		kwds.reserve(a_kwds.size());
		for (const auto& kwdStr : a_kwds) {
			if (const auto kwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(kwdStr)) {
				kwds.push_back(kwd);
			}
		}
		return Utility::HasKeywords(a_form, kwds, a_all);
	}

	long RemoveForms(STATICARGS, RE::TESObjectREFR* a_fromContainer, std::vector<RE::TESForm*> a_forms, RE::TESObjectREFR* a_toContainer)
	{
    if (!a_fromContainer) {
      TRACESTACK("RemoveForms: fromContainer is nullptr");
      return 0;
    }
		long totalRemoved = 0;
		if (!a_fromContainer) {
			return totalRemoved;
		}
		std::unordered_set<RE::TESForm*> formsToRemove(a_forms.begin(), a_forms.end());
		auto removeReason = a_toContainer ? RE::ITEM_REMOVE_REASON::kStoreInContainer : RE::ITEM_REMOVE_REASON::kRemove;
		auto inventory = a_fromContainer->GetInventory();
		auto counts = a_fromContainer->GetInventoryCounts();
		for (const auto& [form, data] : inventory) {
			if (!form->GetPlayable() || form->GetName()[0] == '\0')
				continue;
			if (data.second->IsQuestObject())
				continue;
			if (formsToRemove.contains(form)) {
				auto count = counts[form];
				a_fromContainer->RemoveItem(form, count, removeReason, nullptr, a_toContainer);
				totalRemoved += count;
			}
		}
		return totalRemoved;
	}

	std::string GetButtonForDXScanCode(RE::StaticFunctionTag*, int a_keyCode)
	{
		return PyramidUtils::Input::GetButtonForDXScanCode(a_keyCode);
	}

	std::string ReplaceAt(RE::StaticFunctionTag*, std::string a_str, int a_index, std::string a_replacement)
	{
		a_str.replace(a_index, a_replacement.size(), a_replacement);
		return a_str;
	}

	RE::TESObjectREFR* GetQuestMarker(STATICARGS, RE::TESQuest* a_quest)
	{
    if (!a_quest) {
      TRACESTACK("GetQuestMarker: quest is nullptr");
      return nullptr;
    }
		return PyramidUtils::MarkerManager::GetQuestMarker(a_quest);
	}

	std::vector<RE::TESWorldSpace*> GetExteriorWorldSpaces(STATICARGS, RE::TESObjectCELL* a_cell)
	{
    if (!a_cell) {
      TRACESTACK("GetExteriorWorldSpaces: cell is nullptr");
      return std::vector<RE::TESWorldSpace*>{};
    }
		return Geography::GetWorldSpaces(a_cell);
	}

	std::vector<RE::BGSLocation*> GetExteriorLocations(STATICARGS, RE::TESObjectCELL* a_cell)
	{
    if (!a_cell) {
      TRACESTACK("GetExteriorLocations: cell is nullptr");
      return std::vector<RE::BGSLocation*>{};
    }
		std::vector<RE::BGSLocation*> locs;
		for (const auto& wrld : Geography::GetWorldSpaces(a_cell)) {
			locs.push_back(wrld->location);
		}
		return locs;
	}

	std::vector<RE::TESForm*> GetInventoryNamedObjects(STATICARGS, RE::TESObjectREFR* a_container,
			std::vector<std::string> itemNames)
	{
    if (!a_container) {
      TRACESTACK("GetInventoryNamedObjects: container is nullptr");
      return std::vector<RE::TESForm*>{};
    }
		std::vector<RE::TESForm*> refrs;
		auto inventory = a_container->GetInventory();
		for (const auto& [form, data] : inventory) {
			if (!form->GetPlayable() || form->GetName()[0] == '\0')
				continue;
			if (data.second->IsQuestObject())
				continue;
			std::string formName = form->GetName();
			for (const auto& iName : itemNames) {
				std::string itemName(iName);
        Utility::ToLower(itemName);
        Utility::ToLower(formName);
				logger::info("Processing item {} with tag {}", formName, itemName);
				if (formName.find(itemName) != std::string::npos) {
					refrs.push_back(form);
				}
			}
		}
		return refrs;
	}

	float GetTemperFactor(STATICARGS, RE::TESObjectREFR* a_container, RE::TESForm* a_form)
	{
    if (!a_container) {
      TRACESTACK("GetTemperFactor: container is nullptr");
      return 0.f;
    }
    if (!a_form) {
      TRACESTACK("GetTemperFactor: form is nullptr");
      return 0.f;
    }
		const auto& inventory = a_container->GetInventory();
		for (const auto& [item, meta] : inventory) {
			const auto& [_, data] = meta;
			if (item->GetFormID() == a_form->GetFormID()) {
				if (data->extraLists) {
					for (const auto& list : (*data->extraLists)) {
						if (const auto extraData = list->GetByType<RE::ExtraTextDisplayData>()) {
							return extraData->temperFactor;
						}
					}
				}
			}
		}
		return 0.f;
	}

	float GetTravelDistance(STATICARGS, RE::TESObjectREFR* a_ref1, RE::TESObjectREFR* a_ref2)
	{
    if (!a_ref1) {
      TRACESTACK("GetTravelDistance: ref1 is nullptr");
      return 0.f;
    }
    if (!a_ref2) {
      TRACESTACK("GetTravelDistance: ref2 is nullptr");
      return 0.f;
    }
		return Geography::GetDistanceBetween(a_ref1, a_ref2);
	}

	float GetAbsPosX(STATICARGS, RE::TESObjectREFR* a_ref)
	{
    if (!a_ref) {
      TRACESTACK("GetAbsPosX: ref is nullptr");
      return 0.f;
    }
		return Geography::GetRealPosition(a_ref).x;
	}

	float GetAbsPosY(STATICARGS, RE::TESObjectREFR* a_ref)
	{
    if (!a_ref) {
      TRACESTACK("GetAbsPosY: ref is nullptr");
      return 0.f;
    }
		return Geography::GetRealPosition(a_ref).y;
	}

	float GetAbsPosZ(STATICARGS, RE::TESObjectREFR* a_ref)
	{
    if (!a_ref) {
      TRACESTACK("GetAbsPosZ: ref is nullptr");
      return 0.f;
    }
		return Geography::GetRealPosition(a_ref).z;
	}
}
