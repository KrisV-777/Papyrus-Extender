#include "Hooks.h"

#include "Data/ActorManager.h"
#include "Data/QuestMarker.h"
#include "Patch.h"
#include "common/KrisV/Hooks.h"

namespace Hooks
{
    void Manager::Install()
    {
        logger::info("installing hooks");

        _DoDetect = KrisV::InstallCall(KrisV::kDoDetect, DoDetect);
        _UpdateCombat = KrisV::InstallVFunc(RE::Character::VTABLE[0], 0x0E4, UpdateCombat);
        _ApplyMovementDelta = KrisV::InstallCall(KrisV::kApplyMovementDelta, ApplyMovementDelta);
        _GetQuestMarkerRef = KrisV::InstallCall(KrisV::kGetQuestMarkerRef, GetQuestMarkerRef);

        HINSTANCE dllHandle = LoadLibrary(TEXT("CompassNavigationOverhaul.dll"));
        if (dllHandle != NULL) {
            logger::info("installing cno patch");
            Patch::Install();
        } else {
            logger::info("installing cno hook");
            _UpdateQuests = KrisV::InstallCall(KrisV::kUpdateQuests, UpdateQuests);
        }
    }

    void Manager::UpdateCombat(RE::Character* a_this)
    {
        if (!Data::ActorManager::GetSingleton()->IsCalmed(a_this)) {
            _UpdateCombat(a_this);
        } else if (a_this->IsInCombat()) {
            a_this->StopCombat();
        }
    }

    void Manager::ApplyMovementDelta(RE::Actor* a_actor, float a_delta)
    {
        if (!Data::ActorManager::GetSingleton()->IsCollisionFrozen(a_actor)) {
            _ApplyMovementDelta(a_actor, a_delta);
        }
    }

    uint8_t* Manager::DoDetect(RE::Actor* viewer, RE::Actor* target, int32_t& detectval, uint8_t& unk04, uint8_t& unk05, uint32_t& unk06, RE::NiPoint3& pos, float& unk08, float& unk09, float& unk10)
    {
        const auto actManager = Data::ActorManager::GetSingleton();
        if (viewer && actManager->IsCalmed(viewer) || target && actManager->IsCalmed(target)) {
            detectval = -1000;
            return nullptr;
        }
        return _DoDetect(viewer, target, detectval, unk04, unk05, unk06, pos, unk08, unk09, unk10);
    }

    RE::RefHandle Manager::GetQuestMarkerRef(int64_t a_1, int64_t a_2, RE::TESQuest* a_3)
    {
        Data::QuestMarkerData::SetQuest(a_3);
        return _GetQuestMarkerRef(a_1, a_2, a_3);
    }

    bool Manager::UpdateQuests(void* a_1, void* a_2, RE::NiPoint3* a_3, const RE::RefHandle& a_refHandle, std::int32_t a_5)
    {
        const auto marker = RE::TESObjectREFR::LookupByHandle(a_refHandle).get();
        Data::QuestMarkerData::SetMarker(marker);
        return _UpdateQuests(a_1, a_2, a_3, a_refHandle, a_5);
    }
}
