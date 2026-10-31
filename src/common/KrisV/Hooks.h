#pragma once

#include "common/HookData.h"

namespace KrisV
{
    // uint8_t* DoDetect(RE::Actor* viewer, RE::Actor* target, int32_t& detectval, uint8_t& unk04, uint8_t& unk05, uint32_t& unk06, RE::NiPoint3& pos, float& unk08, float& unk09, float& unk10)
    static constexpr Hooks::HookData kDoDetect{ REL::RelocationID{ 41659, 42742 }, REL::VariantOffset{ 0x526, 0x67B, 0x67B } };

    // void Manager::ApplyMovementDelta(RE::Actor* a_actor, float a_delta)
    static constexpr Hooks::HookData kApplyMovementDelta{ REL::RelocationID{ 36359, 37350 }, REL::VariantOffset{ 0xF0, 0xFB, 0xFB } };
    
    // RE::RefHandle GetQuestMarkerRef(int64_t a_1, int64_t a_2, RE::TESQuest* a_3)
    static constexpr Hooks::HookData kGetQuestMarkerRef{ REL::RelocationID{ 50826, 51691 }, REL::VariantOffset{ 0xFB, 0x167, 0xFB } };
    
    // bool UpdateQuests(void* a_1, void* a_2, RE::NiPoint3* a_3, const RE::RefHandle& a_refHandle, std::int32_t a_5)
    static constexpr Hooks::HookData kUpdateQuests{ REL::RelocationID{ 50826, 51691 }, REL::VariantOffset{ 0x114, 0x180, 0x114 } };
}
