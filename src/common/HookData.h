#pragma once

namespace Hooks
{
    struct HookData
    {
        constexpr explicit HookData(REL::RelocationID a_relocation, REL::VariantOffset a_offset) noexcept :
          relocation(a_relocation), offset(a_offset) {}

        REL::RelocationID relocation;
        REL::VariantOffset offset;

        [[nodiscard]] std::uintptr_t address() const
        {
            const REL::Relocation<std::uintptr_t> target{ relocation, offset };
            return target.address();
        }
    };

    template <class T>
    inline auto InstallHook(HookData a_hook, T a_target)
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