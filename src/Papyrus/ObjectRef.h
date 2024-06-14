#pragma once

namespace Papyrus::ObjectRef
{
	std::vector<RE::TESObjectREFR*> GetContainer(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESForm* a_form);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetContainer, "SPE_ObjectRef", true);

		return true;
	}
} // namespace Papyrus::ObjectRef
