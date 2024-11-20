#pragma once

namespace Papyrus::Cell
{
	std::vector<RE::TESWorldSpace*> GetExteriorWorldSpaces(STATICARGS, RE::TESObjectCELL* a_cell);
	std::vector<RE::BGSLocation*> GetExteriorLocations(STATICARGS, RE::TESObjectCELL* a_cell);

	inline bool Register(VM* a_vm)
	{
    REGISTERFUNC(GetExteriorWorldSpaces, "SPE_Cell", true);
    REGISTERFUNC(GetExteriorLocations, "SPE_Cell", true);

		return true;
	}
}	 // namespace Papyrus::Cell
