#pragma once

namespace Papyrus::GlobalVariable
{
	RE::TESGlobal* GetGlobal(RE::StaticFunctionTag*, RE::BSFixedString a_edid);

	inline bool Register(VM* a_vm)
	{
		REGISTERFUNC(GetGlobal, "SPE_GlobalVariable", false);

		return true;
	}
}	 // namespace Papyrus::GlobalVariable
