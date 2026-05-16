#include "Cell.h"

#include "Util/Geography.h"

namespace Papyrus::Cell
{
    std::vector<RE::TESWorldSpace*> GetExteriorWorldSpaces(STATICARGS, RE::TESObjectCELL* a_cell)
    {
        if (!a_cell) {
            TRACESTACK("Cell is null");
            return std::vector<RE::TESWorldSpace*>{};
        }
        return Geography::GetWorldSpaces(a_cell);
    }

    std::vector<RE::BGSLocation*> GetExteriorLocations(STATICARGS, RE::TESObjectCELL* a_cell)
    {
        if (!a_cell) {
            TRACESTACK("Cell is null");
            return std::vector<RE::BGSLocation*>{};
        }
        const auto wrldSpaces = Geography::GetWorldSpaces(a_cell);
        const auto ret = std::ranges::fold_left(wrldSpaces, std::vector<RE::BGSLocation*>{}, [](auto&& acc, const auto& wrld) {
            return (acc.push_back(wrld->location), acc);
        });
        return ret;
    }

    std::vector<RE::TESObjectCELL*> GetAttachedCells(STATICARGS, uint32_t a_radius)
    {
        const auto TES = RE::TES::GetSingleton();
        if (auto cell = TES->interiorCell; cell) {
            return { cell };
        }

        std::vector<RE::TESObjectCELL*> result;
        const auto gridCells = TES->gridCells;
        const auto gridLength = gridCells ? gridCells->length : 0;
        if (gridLength == 0) {
            return result;
        } else if (gridLength > static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max())) {
            a_vm->TraceStack(std::format("Unexpectedly high grid length: {}.", gridLength).c_str(), a_stackID);
            return result;
        } else if (gridLength % 2 == 0) {
            logger::warn("Unexpected even grid length: {}", gridLength);
        }

        const auto len = static_cast<std::int32_t>(gridLength);
        const auto radius = static_cast<std::int32_t>(a_radius);
        const std::int32_t center = len / 2;
        const std::int32_t minX = std::max(0, center - radius);
        const std::int32_t maxX = std::min(len - 1, center + radius);
        const std::int32_t minY = std::max(0, center - radius);
        const std::int32_t maxY = std::min(len - 1, center + radius);

        for (std::int32_t x = minX; x <= maxX; ++x) {
            for (std::int32_t y = minY; y <= maxY; ++y) {
                auto cell = gridCells->GetCell(x, y);
                if (cell && cell->IsAttached()) {
                    result.push_back(cell);
                }
            }
        }

        return result;
    }

    RE::BGSLocation* GetWorldSpaceLocation(STATICARGS, RE::TESWorldSpace* a_world)
    {
        if (!a_world) {
            TRACESTACK("World space is null");
            return nullptr;
        }
        return a_world->location;
    }

    RE::BGSLocation* GetCellLocation(STATICARGS, RE::TESObjectCELL* a_cell)
    {
        if (!a_cell) {
            TRACESTACK("Cell is null");
            return nullptr;
        }
        return a_cell->GetLocation();
    }

}  // namespace Papyrus::Cell
