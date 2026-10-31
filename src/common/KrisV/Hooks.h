#pragma once

namespace KrisV
{
    namespace Hooks
    {
        struct HookInfo
        {
            constexpr explicit HookInfo(REL::RelocationID a_relocation, REL::VariantOffset a_offset) noexcept :
              relocation(a_relocation), offset(a_offset) {}

            REL::RelocationID relocation;
            REL::VariantOffset offset;

            [[nodiscard]] std::uintptr_t address() const
            {
                const REL::Relocation<std::uintptr_t> target{ relocation, offset };
                return target.address();
            }
        };

        static constexpr HookInfo kDoDetect{ REL::RelocationID{ 41659, 42742 }, REL::VariantOffset{ 0x526, 0x67B, 0x67B } };
        static constexpr HookInfo kApplyMovementDelta{ REL::RelocationID{ 36359, 37350 }, REL::VariantOffset{ 0xF0, 0xFB, 0xFB } };
        static constexpr HookInfo kGetQuestMarkerRef{ REL::RelocationID{ 50826, 51691 }, REL::VariantOffset{ 0xFB, 0x167, 0xFB } };
        static constexpr HookInfo kUpdateQuests{ REL::RelocationID{ 50826, 51691 }, REL::VariantOffset{ 0x114, 0x180, 0x114 } };

        template <class T>
        inline auto InstallCall(HookInfo a_hook, T a_target)
        {
            auto& trampoline = SKSE::GetTrampoline();
            return trampoline.write_call<5>(a_hook.address(), a_target);
        }

        template <class T>
        inline auto InstallVFunc(const auto& a_vtable, std::size_t a_index, T a_target)
        {
            REL::Relocation<std::uintptr_t> vtable{ a_vtable.address() };
            return vtable.write_vfunc(a_index, a_target);
        }
    }

    using namespace Hooks;
}