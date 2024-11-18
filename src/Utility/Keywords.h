#pragma once

namespace Utility
{
	bool HasKeywords(RE::TESForm* a_form, std::vector<RE::BGSKeyword*> a_kwds, bool a_matchAll)
  {
		auto keywordForm = a_form->As<RE::BGSKeywordForm>();
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

} // namespace Utility
