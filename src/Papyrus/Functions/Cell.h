#pragma once

namespace Papyrus::Cell
{
    std::vector<RE::TESWorldSpace*> GetExteriorWorldSpaces(STATICARGS, RE::TESObjectCELL* a_cell);
    std::vector<RE::BGSLocation*> GetExteriorLocations(STATICARGS, RE::TESObjectCELL* a_cell);
    std::vector<RE::TESObjectCELL*> GetAttachedCells(STATICARGS, uint32_t a_radius);
    RE::BGSLocation* GetWorldSpaceLocation(STATICARGS, RE::TESWorldSpace* a_world);
    RE::BGSLocation* GetCellLocation(STATICARGS, RE::TESObjectCELL* a_cell);

    inline bool Register(VM* a_vm)
    {
        REGISTERFUNC(GetExteriorWorldSpaces, "SPE_Cell", true);
        REGISTERFUNC(GetExteriorLocations, "SPE_Cell", true);
        REGISTERFUNC(GetAttachedCells, "SPE_Cell", true);
        REGISTERFUNC(GetWorldSpaceLocation, "SPE_Cell", true);
        REGISTERFUNC(GetCellLocation, "SPE_Cell", true);

        return true;
    }
}  // namespace Papyrus::Cell
