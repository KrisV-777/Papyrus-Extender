#include "ActorManager.h"

#include "Serialization/Utility.h"

namespace Data
{
	void ActorManager::SetActorCalmed(RE::Actor* a_actor, bool a_calmed)
	{
		if (a_calmed) {
			calmed.insert(a_actor->GetFormID());
		} else {
			calmed.erase(a_actor->GetFormID());
		}
	}

	void ActorManager::SetActorFrozen(RE::Actor* a_actor, bool a_enabled)
	{
		a_actor->SetCollision(a_enabled);

		if (a_enabled) {
			disabledCollision.insert(a_actor->GetFormID());
		} else {
			disabledCollision.erase(a_actor->GetFormID());
		}
	}

	bool ActorManager::IsCollisionFrozen(RE::Actor* a_actor)
	{
		return disabledCollision.contains(a_actor->GetFormID());
	}

	bool ActorManager::IsCalmed(RE::Actor* a_actor)
	{
		return calmed.contains(a_actor->GetFormID());
	}

	void ActorManager::Save(SKSE::SerializationInterface* a_intfc) const
	{
		Serialization::SaveFormIDs(a_intfc, calmed);
		Serialization::SaveFormIDs(a_intfc, disabledCollision);
		logger::info("Wrote {} and {} actors into co-save", calmed.size(), disabledCollision.size());
	}

	void ActorManager::Load(SKSE::SerializationInterface* a_intfc)
	{
		Serialization::LoadFormIDs(a_intfc, calmed);
		Serialization::LoadFormIDs(a_intfc, disabledCollision);
		logger::info("Read {} and {} actors from co-save", calmed.size(), disabledCollision.size());
	}

	void ActorManager::Revert(SKSE::SerializationInterface*)
	{
		calmed.clear();
		disabledCollision.clear();
	}
}	 // namespace Data
