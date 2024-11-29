#pragma once

namespace Keywords
{
	inline RE::BGSKeywordForm* AsKeywordForm(RE::TESForm* a_form)
	{
		if (const auto arrowForm = a_form->As<RE::TESAmmo>()) {
			return arrowForm->AsKeywordForm();
		} else {
			return a_form->As<RE::BGSKeywordForm>();
		}
	}

	inline bool HasKeywords(RE::TESForm* a_form, std::vector<RE::BGSKeyword*> a_kwds, bool a_matchAll)
  {
		auto keywordForm = AsKeywordForm(a_form);
		if (!keywordForm) {
			return false;
		}
		for (const auto& kwd : a_kwds) {
			if (!kwd) {
				continue;
			} else if (keywordForm->HasKeyword(kwd)) {
				if (!a_matchAll) {
					return true;
				}
			} else {
				if (a_matchAll) {
					return false;
				}
			}
		}
		return false;
  }

}	 // namespace Keywords
