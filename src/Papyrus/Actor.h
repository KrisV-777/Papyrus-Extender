#pragma once

namespace Papyrus::Actor
{
	RE::BSFixedString GetRaceType(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetRaceType, "SPE_Actor", false);

		return true;
	};

} // namespace Papyrus::Actor
