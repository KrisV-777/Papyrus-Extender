#pragma once

namespace Papyrus::Form
{
	std::vector<RE::TESObjectREFR*> GetContainer(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESForm* a_form);
	std::vector<RE::TESForm*> FlattenLeveledList(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESLevItem* a_list);

	bool FormHasKeywords(STATICARGS, RE::TESForm* a_form, std::vector<RE::BGSKeyword*> a_kwds, bool a_all);
	bool FormHasKeywordStrings(STATICARGS, RE::TESForm* a_form, std::vector<std::string> a_kwds, bool a_all, bool a_partialmatch);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetContainer, "SPE_Form", true);
		REGISTERFUNC(FlattenLeveledList, "SPE_Form", true);

		REGISTERFUNC(FormHasKeywords, "SPE_Form", true);
		REGISTERFUNC(FormHasKeywordStrings, "SPE_Form", true);

		return true;
	}
} // namespace Papyrus::Form
