#include "GlobalVariable.h"

namespace Papyrus::GlobalVariable
{
	RE::TESGlobal* GetGlobal(RE::StaticFunctionTag*, RE::BSFixedString a_edid)
	{
		return RE::TESForm::LookupByEditorID<RE::TESGlobal>(a_edid);
	}

}	 // namespace Papyrus::GlobalVariable
