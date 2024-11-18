#pragma once

namespace Data
{
	class ActorManager :
		public Singleton<ActorManager>
	{
	public:
		void SetActorCalmed(RE::Actor* a_actor, bool a_calmed);
		void SetActorFrozen(RE::Actor* a_actor, bool a_enabled);

		bool IsCalmed(RE::Actor* a_actor);
		bool IsCollisionFrozen(RE::Actor* a_actor);

		void Save(SKSE::SerializationInterface* a_intfc) const;
		void Load(SKSE::SerializationInterface* a_intfc);
		void Revert(SKSE::SerializationInterface* a_intfc);

	private:
		std::set<RE::FormID> calmed;
		std::set<RE::FormID> disabledCollision;
	};
}
