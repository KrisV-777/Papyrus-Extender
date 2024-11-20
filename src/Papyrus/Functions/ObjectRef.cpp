#include "ObjectRef.h"

#include "Util/Keywords.h"
#include "Util/Geography.h"

namespace Papyrus::ObjectRef
{
	std::vector<RE::TESForm*> GetEnchantedItems(STATICARGS, RE::TESObjectREFR* a_ref, bool a_weapons, bool a_armors, bool a_wornonly)
  {
    if (!a_ref) {
      TRACESTACK("Ref is nullptr");
      return std::vector<RE::TESForm*>{};
    }
    std::vector<RE::TESForm*> items;
		auto inv = a_ref->GetInventory([&](RE::TESBoundObject& a_object) {
			return (a_object.IsArmor() && a_armors || a_object.IsWeapon() && a_weapons) && a_object.GetPlayable() && a_object.GetName()[0] != '\0';
		});
		for (const auto& [form, data] : inv) {
			if (!data.second->GetEnchantment() || a_wornonly && !data.second->IsWorn()) {
        continue;
      }
      items.push_back(form);
		}
    return items;
  }
  
  std::vector<RE::TESForm*> GetInventoryNamedObjects(STATICARGS, RE::TESObjectREFR* a_ref, std::vector<RE::BSFixedString> itemNames)
  {
    if (!a_ref) {
      TRACESTACK("Ref is nullptr");
      return std::vector<RE::TESForm*>{};
    }
    std::vector<RE::TESForm*> items;
		auto inv = a_ref->GetInventory([&](RE::TESBoundObject& a_object) { return a_object.GetPlayable(); });
		for (const auto& [form, data] : inv) {
			RE::BSFixedString formName { form->GetName() };
			if (itemNames.empty() || std::ranges::contains(itemNames, formName)) {
				items.push_back(form);
			}
		}
		return items;
  }

	std::vector<RE::TESForm*> GetItemsByKeyword(STATICARGS, RE::TESObjectREFR* a_container, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall)
  {
    if (!a_container) {
      TRACESTACK("Container is nullptr");
      return std::vector<RE::TESForm*>{};
    }
    std::vector<RE::TESForm*> items;
    auto inv = a_container->GetInventory([&](RE::TESBoundObject& a_object) {
      return a_object.GetPlayable() && a_object.GetName()[0] != '\0';
    });
    for (const auto& [form, data] : inv) {
      if (a_keywords.empty() || Keywords::HasKeywords(form, a_keywords, a_matchall)) {
        items.push_back(form);
      }
    }
    return items;
  }

	int32_t RemoveItems(STATICARGS, RE::TESObjectREFR* a_reference, std::vector<RE::TESForm*> a_forms, RE::TESObjectREFR* a_target)
  {
    if (!a_reference) {
      TRACESTACK("Reference is nullptr");
      return 0;
		}
		long totalRemoved = 0;
    auto removeReason = a_target ? RE::ITEM_REMOVE_REASON::kStoreInContainer : RE::ITEM_REMOVE_REASON::kRemove;
		auto inventory = a_reference->GetInventory([&](RE::TESBoundObject& a_object) {
			return a_object.GetPlayable() && a_object.GetName()[0] != '\0';
		});
		auto counts = a_reference->GetInventoryCounts();
		for (const auto& [form, data] : inventory) {
			if (data.second->IsQuestObject())
				continue;
			if (!std::ranges::contains(a_forms, form))
        continue;
			a_reference->RemoveItem(form, data.first, removeReason, nullptr, a_target);
			totalRemoved += data.first;
		}
		return totalRemoved;
  }

	float GetTemperFactor(STATICARGS, RE::TESObjectREFR* a_reference, RE::TESForm* a_form)
  {
    if (!a_reference) {
      TRACESTACK("Reference is nullptr");
      return 0.0f;
    }
    if (!a_form) {
      TRACESTACK("Form is nullptr");
      return 0.0f;
		}
		const auto& inventory = a_reference->GetInventory();
		for (const auto& [item, meta] : inventory) {
			const auto& [_, data] = meta;
			if (item->GetFormID() != a_form->GetFormID())
				continue;
			if (!data->extraLists)
				continue;
			for (const auto& list : (*data->extraLists)) {
				if (const auto extraData = list->GetByType<RE::ExtraTextDisplayData>()) {
					return extraData->temperFactor;
				}
			}
		}
		return 0.0f;
	}
  
	float GetTravelDistance(STATICARGS, RE::TESObjectREFR* a_ref1, RE::TESObjectREFR* a_ref2)
	{
    if (!a_ref1) {
      TRACESTACK("Ref1 is nullptr");
      return 0.f;
    }
    if (!a_ref2) {
      TRACESTACK("Ref2 is nullptr");
      return 0.f;
    }
		return Geography::GetDistanceBetween(a_ref1, a_ref2);
	}

	float GetAbsPosX(STATICARGS, RE::TESObjectREFR* a_ref)
	{
    if (!a_ref) {
      TRACESTACK("Ref is nullptr");
      return 0.f;
    }
		return Geography::GetRealPosition(a_ref).x;
	}

	float GetAbsPosY(STATICARGS, RE::TESObjectREFR* a_ref)
	{
    if (!a_ref) {
      TRACESTACK("Ref is nullptr");
      return 0.f;
    }
		return Geography::GetRealPosition(a_ref).y;
	}

	float GetAbsPosZ(STATICARGS, RE::TESObjectREFR* a_ref)
	{
    if (!a_ref) {
      TRACESTACK("Ref is nullptr");
      return 0.f;
    }
		return Geography::GetRealPosition(a_ref).z;
	}

}	// namespace Papyrus::ObjectRef
