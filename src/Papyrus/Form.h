#pragma once

namespace Papyrus::Form
{
	std::vector<RE::TESObjectREFR*> GetContainer(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESForm* a_form);
	std::vector<RE::TESForm*> FlattenLeveledList(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESLevItem* a_list);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetContainer, "SPE_Form", true);
		REGISTERFUNC(FlattenLeveledList, "SPE_Form", true);

		return true;
	}
} // namespace Papyrus::Form
