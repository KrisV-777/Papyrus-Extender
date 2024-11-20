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
		std::vector<RE::BGSLocation*> locs;
		for (const auto& wrld : Geography::GetWorldSpaces(a_cell)) {
			locs.push_back(wrld->location);
		}
		return locs;
	}
} // namespace Papyrus::Cell
