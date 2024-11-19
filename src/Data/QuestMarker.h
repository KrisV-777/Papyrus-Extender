#pragma once

namespace Data
{
	struct QuestMarkerData final
	{
		QuestMarkerData() = delete;

		static inline void SetQuest(RE::TESQuest* a_quest) { _quest = a_quest; }
		static inline void SetMarker(RE::TESObjectREFR* a_ref) { _markers[_quest] = a_ref; }
		static inline RE::TESObjectREFR* GetQuestMarker(RE::TESQuest* a_quest) { return _markers.contains(a_quest) ? _markers[a_quest] : nullptr; }

	private:
		static inline std::unordered_map<RE::TESQuest*, RE::TESObjectREFR*> _markers;
		static inline RE::TESQuest* _quest = nullptr;
	};
}