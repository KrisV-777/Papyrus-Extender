#include "Quest.h"

#include "Data/QuestMarker.h"

namespace Papyrus::Quest
{
	RE::TESObjectREFR* GetQuestMarker(STATICARGS, RE::TESQuest* a_quest)
  {
		if (!a_quest) {
			TRACESTACK("GetQuestMarker: quest is nullptr");
			return nullptr;
		}
		return Data::QuestMarkerData::GetQuestMarker(a_quest);
	}

} // namespace Papyrus::Quest
