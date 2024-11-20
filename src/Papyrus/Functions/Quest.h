#pragma once

namespace Papyrus::Quest
{
	RE::TESObjectREFR* GetQuestMarker(STATICARGS, RE::TESQuest* a_quest);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetQuestMarker, "SPE_Quest", true);

		return true;
	}
} // namespace Papyrus::Quest
