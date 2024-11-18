#include "Actor.h"

#undef GetObject
#undef min
#undef max

#include <frozen/string.h>
#include <frozen/map.h>

#include "Data/ActorManager.h"
#include "Utility/Keywords.h"

namespace Papyrus::Actor
{
	RE::BSFixedString GetRaceType(STATICARGS, RE::Actor* a_actor)
	{
    if (!a_actor) {
			TRACESTACK("Actor is null");
      return "";
    }
		const auto base = a_actor->GetActorBase();
		const auto race = a_actor->GetRace();
		const auto sex = base->GetSex();
		if (!race || !base || sex == RE::SEXES::kNone) {
			logger::critical("Actor {:X} (using Base: {:X}) has no race/base/sex", a_actor->GetFormID(), base ? base->GetFormID() : 0);
			return "";
		}
		const std::string_view rootTMP{ race->rootBehaviorGraphNames[sex].data() };
		const auto root{ rootTMP.substr(rootTMP.rfind('\\') + 1) };

		constexpr frozen::map<frozen::string, frozen::string, 45> behaviorfiles{
			{ "0_Master.hkx", "Human" },
			{ "WolfBehavior.hkx", "Wolf" },
			{ "DogBehavior.hkx", "Dog" },
			{ "ChickenBehavior.hkx", "Chicken" },
			{ "HareBehavior.hkx", "Hare" },
			{ "AtronachFlameBehavior.hkx", "FlameAtronach" },
			{ "AtronachFrostBehavior.hkx", "FrostAtronach" },
			{ "AtronachStormBehavior.hkx", "StormAtronach" },
			{ "BearBehavior.hkx", "Bear" },
			{ "ChaurusBehavior.hkx", "Chaurus" },
			{ "H-CowBehavior.hkx", "Cow" },
			{ "DeerBehavior.hkx", "Deer" },
			{ "CHaurusFlyerBehavior.hkx", "ChaurusHunter" },
			{ "VampireBruteBehavior.hkx", "Gargoyle" },
			{ "BenthicLurkerBehavior.hkx", "Lurker" },
			{ "BoarBehavior.hkx", "Boar" },
			{ "BCBehavior.hkx", "DwarvenBallista" },
			{ "HMDaedra.hkx", "Seeker" },
			{ "NetchBehavior.hkx", "Netch" },
			{ "RieklingBehavior.hkx", "Riekling" },
			{ "ScribBehavior.hkx", "AshHopper" },
			{ "DragonBehavior.hkx", "Dragon" },
			{ "Dragon_Priest.hkx", "DragonPriest" },
			{ "DraugrBehavior.hkx", "Draugr" },
			{ "SCBehavior.hkx", "DwarvenSphere" },
			{ "DwarvenSpiderBehavior.hkx", "DwarvenSpider" },
			{ "SteamBehavior.hkx", "DwarvenCenturion" },
			{ "FalmerBehavior.hkx", "Falmer" },
			{ "FrostbiteSpiderBehavior.hkx", "Spider" },
			{ "GiantBehavior.hkx", "Giant" },
			{ "GoatBehavior.hkx", "Goat" },
			{ "HavgravenBehavior.hkx", "Hagraven" },
			{ "HorkerBehavior.hkx", "Horker" },
			{ "HorseBehavior.hkx", "Horse" },
			{ "IceWraithBehavior.hkx", "IceWraith" },
			{ "MammothBehavior.hkx", "Mammoth" },
			{ "MudcrabBehavior.hkx", "Mudcrab" },
			{ "SabreCatBehavior.hkx", "Sabrecat" },
			{ "SkeeverBehavior.hkx", "Skeever" },
			{ "SlaughterfishBehavior.hkx", "Slaughterfish" },
			{ "SprigganBehavior.hkx", "Spriggan" },
			{ "TrollBehavior.hkx", "Troll" },
			{ "VampireLord.hkx", "VampireLord" },
			{ "WerewolfBehavior.hkx", "Werewolf" },
			{ "WispBehavior.hkx", "Wispmother" },
			{ "WitchlightBehavior.hkx", "Wisp" },
		};
		auto where = behaviorfiles.find(root);
		return where == behaviorfiles.end() ? "" : where->second.data();
	}

	void SetActorCalmed(STATICARGS, RE::Actor* a_actor, bool a_calmed)
	{
		if (!a_actor) {
			TRACESTACK("Actor is null");
			return;
		}
		Data::ActorManager::GetSingleton()->SetActorCalmed(a_actor, a_calmed);
	}

	void SetActorFrozen(STATICARGS, RE::Actor* a_target, bool a_frozen)
	{
		if (!a_target) {
			TRACESTACK("Actor is null");
			return;
		}
		Data::ActorManager::GetSingleton()->SetActorFrozen(a_target, a_frozen);
	}

	bool IsActorCalmed(STATICARGS, RE::Actor* a_actor)
	{
		if (!a_actor) {
			TRACESTACK("Actor is null");
			return false;
		}
		return Data::ActorManager::GetSingleton()->IsCalmed(a_actor);
	}

	bool IsActorFrozen(STATICARGS, RE::Actor* a_actor)
	{
		if (!a_actor) {
			TRACESTACK("Actor is null");
			return false;
		}
		return Data::ActorManager::GetSingleton()->IsCollisionFrozen(a_actor);
	}

	std::vector<RE::Actor*> GetDetectedActors(STATICARGS, RE::Actor* a_actor)
	{
		if (!a_actor) {
			TRACESTACK("Actor is null");
			return {};
		}
		std::vector<RE::Actor*> retval;
		const auto processLists = RE::ProcessLists::GetSingleton();
		for (const auto& actorHandle : processLists->highActorHandles) {
			const auto it = actorHandle.get().get();
			if (!it)
				continue;
			if (a_actor->RequestDetectionLevel(it) > 0) {
				retval.push_back(it);
			}
		}
		return retval;
	}

	std::vector<RE::Actor*> GetDetectedBy(STATICARGS, RE::Actor* a_actor)
	{
		if (!a_actor) {
			TRACESTACK("Actor is null");
			return {};
		}
		std::vector<RE::Actor*> retval;
		const auto processLists = RE::ProcessLists::GetSingleton();
		for (const auto& actorHandle : processLists->highActorHandles) {
			const auto it = actorHandle.get().get();
			if (!it)
				continue;
			if (it->RequestDetectionLevel(a_actor) > 0) {
				retval.push_back(it);
			}
		}
		return retval;
	}
	
	std::vector<RE::TESObjectARMO*> GetWornForms(STATICARGS, RE::Actor* a_actor, uint32_t a_slotmask)
	{
		if (!a_actor) {
			TRACESTACK("Actor is null");
			return {};
		}
		std::vector<RE::TESObjectARMO*> ret;
		auto inventory = a_actor->GetInventory([&](RE::TESBoundObject& a_object) {
			return a_object.IsArmor() && a_object.GetPlayable() && a_object.GetName()[0] != '\0';
		});
		for (const auto& [form, data] : inventory) {
			if (!data.second->IsWorn()) {
				continue;
			}
			const auto item = data.second.get();
			const auto armo = item ? item->GetObject()->As<RE::TESObjectARMO>() : nullptr;
			if (!armo) {
				continue;
			} else if (a_slotmask) {
				const auto slots = static_cast<uint32_t>(armo->GetSlotMask());
        if ((slots & a_slotmask) == 0) {
          continue;
        }
			}
			ret.push_back(armo);
		}
		return ret;
	}

	std::vector<RE::BGSKeyword*> WornHasKeywords(STATICARGS, RE::Actor* a_actor, std::vector<RE::BGSKeyword*> a_kwds)
	{
		if (!a_actor) {
			TRACESTACK("Actor is nullptr");
			return std::vector<RE::BGSKeyword*>{};
		}
		std::unordered_set<RE::BGSKeyword*> worn{};
		const auto inv = a_actor->GetInventory([](RE::TESBoundObject& a_object) {
			return a_object.IsArmor();
		});
		for (const auto& [item, invData] : inv) {
			const auto& [count, entry] = invData;
			if (count <= 0 || entry->IsWorn())
				continue;
			const auto kwdItm = item->As<RE::BGSKeywordForm>();
			if (!kwdItm)
				continue;
			for (const auto& kwd : a_kwds) {
				if (kwd && kwdItm->HasKeyword(kwd)) {
					worn.insert(kwd);
				}
			}
		}
		return std::vector<RE::BGSKeyword*>{ worn.begin(), worn.end() };
	}

	std::vector<RE::BGSKeyword*> WornHasKeywordStrings(STATICARGS, RE::Actor* a_actor, std::vector<RE::BSFixedString> a_kwds, bool a_partialmatch)
	{
		if (!a_actor) {
			TRACESTACK("Actor is nullptr");
			return std::vector<RE::BGSKeyword*>{};
		}
		std::unordered_set<RE::BGSKeyword*> worn{};
		const auto inv = a_actor->GetInventory([](RE::TESBoundObject& a_object) {
			return a_object.IsArmor();
		});
		for (const auto& [item, invData] : inv) {
			const auto& [count, entry] = invData;
			if (count <= 0 || entry->IsWorn())
				continue;
			const auto kwdItm = item->As<RE::BGSKeywordForm>();
			if (!kwdItm)
				continue;
			for (auto& kwdStr : a_kwds) {
				if (kwdStr.empty())
					continue;
				if (a_partialmatch) {
					RE::BGSKeyword* kwd = nullptr;
					kwdItm->ForEachKeyword([&](auto* a_keyword) {
						if (a_keyword->formEditorID.contains(kwdStr)) {
							kwd = a_keyword;
							return RE::BSContainer::ForEachResult::kStop;
						}
						return RE::BSContainer::ForEachResult::kContinue;
					});
					if (kwd) {
						worn.insert(kwd);
					}
				} else {
					const auto kwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(kwdStr);
					if (kwd && kwdItm->HasKeyword(kwd)) {
						worn.insert(kwd);
					}
				}
			}
		}
		return std::vector<RE::BGSKeyword*>{ worn.begin(), worn.end() };
	}

	RE::Actor* GetPlayerSpeechTarget(RE::StaticFunctionTag*)
	{
		if (auto speakerObjPtr = RE::MenuTopicManager::GetSingleton()->speaker) {
			if (auto speakerPtr = speakerObjPtr.get()) {
				if (auto speaker = speakerPtr.get()) {
					return speaker->As<RE::Actor>();
				}
			}
		}
		return nullptr;
	}

	void Dismount(STATICARGS, RE::Actor* a_actor)
	{
		if (!a_actor) {
			TRACESTACK("Dismount: actor is null");
			return;
		}
		// source: BTPS (https://gitlab.com/Shrimperator/skyrim-mod-betterthirdpersonselection)
		typedef __int64(__fastcall DismountActor_func)(RE::Actor*);
		static auto DismountActor = RELOCATION_ID(36882, 37906);
		static auto dismount = REL::Relocation<DismountActor_func>{ DismountActor };
		dismount(a_actor);
	}

} // namespace Papyrus::Actor
