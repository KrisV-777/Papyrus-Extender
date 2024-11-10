#pragma once

namespace Papyrus::Location
{
	RE::BGSLocation* GetParentLocation(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BGSLocation* a_location);

	inline bool Register(VM* a_vm)
	{
    REGISTERFUNC(GetParentLocation, "SPE_Location", false);

		return true;
	}
} // namespace Papyrus::Location
