#pragma once

#include "Data/QuestMarker.h"

#include <xbyak/xbyak.h>

namespace Hooks::Patch
{
    void UpdateQuests(void*, void*, RE::NiPoint3*, const RE::RefHandle& a_refHandle, std::uint32_t)
    {
        const auto marker = RE::TESObjectREFR::LookupByHandle(a_refHandle).get();
        Data::QuestMarkerData::SetMarker(marker);
    }

    std::uintptr_t getJmpTarget(std::uintptr_t a_addr)
    {
        uint8_t opcode = *(uint8_t*)a_addr;

        if (opcode != 0xE9)
            return (uintptr_t)-1;

        int32_t offset = *(int32_t*)(a_addr + 1);

        uintptr_t target = a_addr + 5 + offset;

        return target;
    }

    struct HookCodeGenerator : Xbyak::CodeGenerator
    {
        HookCodeGenerator(std::uintptr_t a_cnoAddr)
        {
            Xbyak::Label hookLabel;
            Xbyak::Label cnoLabel;

            push(rcx);
            push(rdx);
            push(r8);
            push(r9);

            call(ptr[rip + hookLabel]);

            pop(r9);
            pop(r8);
            pop(rdx);
            pop(rcx);

            jmp(ptr[rip + cnoLabel]);

            L(hookLabel), dq(reinterpret_cast<std::uintptr_t>(&UpdateQuests));
            L(cnoLabel), dq(a_cnoAddr);

            ready();
        }
    };

    void Install()
    {
        const auto address = REL::RelocationID{ 50826, 51691 }.address() + REL::VariantOffset{ 0x114, 0x180, 0x114 }.offset();
        const auto target = getJmpTarget(address);

        if (target == static_cast<std::uintptr_t>(-1)) {
            logger::error("Failed to locate CNO jump target for quest marker patch");
            return;
        }

        auto& trampoline = SKSE::GetTrampoline();
        HookCodeGenerator hookCode{ target };
        auto* hookTarget = trampoline.allocate(hookCode);
        trampoline.write_branch<5>(address, reinterpret_cast<std::uintptr_t>(hookTarget));
    }
}