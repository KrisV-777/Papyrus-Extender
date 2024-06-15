#pragma once

namespace Papyrus::Form
{
	std::vector<RE::TESObjectREFR*> GetContainer(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESForm* a_form);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetContainer, "SPE_Form", true);

		return true;
	}
} // namespace Papyrus::Form
