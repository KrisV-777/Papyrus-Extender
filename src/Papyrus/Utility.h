#pragma once

namespace Papyrus::Util
{
	namespace Array
	{
		void Shuffle_Int(RE::StaticFunctionTag*, RE::reference_array<int> arr);
		void Shuffle_Float(RE::StaticFunctionTag*, RE::reference_array<float> arr);
		void Shuffle_String(RE::StaticFunctionTag*, RE::reference_array<RE::BSFixedString> arr);

		bool Sort_Int(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<int> arr, std::string lua);
		bool Sort_Float(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<float> arr, std::string lua);
		bool Sort_String(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<RE::BSFixedString> arr, std::string lua);

		int32_t FindIf_Int(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<int> arr, std::string lua);
		int32_t FindIf_Float(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<float> arr, std::string lua);
		int32_t FindIf_String(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<RE::BSFixedString> arr, std::string lua);

		std::vector<int> RemoveIf_Int(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<int> arr, std::string lua);
		std::vector<float> RemoveIf_Float(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<float> arr, std::string lua);
		std::vector<RE::BSFixedString> RemoveIf_String(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, std::string lua);

		std::vector<RE::TESForm*> FilterArray_Form(RE::StaticFunctionTag*, std::vector<RE::TESForm*> arr, std::vector<RE::TESForm*> filter);
		std::vector<int> FilterArray_Int(RE::StaticFunctionTag*, std::vector<int> arr, std::vector<int> filter);
		std::vector<float> FilterArray_Float(RE::StaticFunctionTag*, std::vector<float> arr, std::vector<float> filter);
		std::vector<RE::BSFixedString> FilterArray_String(RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, std::vector<RE::BSFixedString> filter);

		std::vector<RE::TESForm*> FilterFormsByKeyword(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall, bool a_invert);
		std::vector<RE::TESForm*> FilterFormsByGoldValue(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, int a_value, bool a_greater, bool a_equal);
		std::vector<RE::TESObjectARMO*> FilterBySlot(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, std::vector<int> a_slots, bool a_all);
		std::vector<RE::TESObjectARMO*> FilterBySlotmask(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, uint32_t a_slotmask, bool a_all);

		std::vector<int> PushFront_Int(RE::StaticFunctionTag*, std::vector<int> arr, int push);
		std::vector<float> PushFront_Float(RE::StaticFunctionTag*, std::vector<float> arr, float push);
		std::vector<RE::BSFixedString> PushFront_String(RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, RE::BSFixedString push);

		inline void Register(VM* a_vm)
		{
			REGISTERFUNC(Shuffle_Int, "SPE_Utility", false);
			REGISTERFUNC(Shuffle_Float, "SPE_Utility", false);
			REGISTERFUNC(Shuffle_String, "SPE_Utility", false);

			REGISTERFUNC(Sort_Int, "SPE_Utility", false);
			REGISTERFUNC(Sort_Float, "SPE_Utility", false);
			REGISTERFUNC(Sort_String, "SPE_Utility", false);

			REGISTERFUNC(FindIf_Int, "SPE_Utility", false);
			REGISTERFUNC(FindIf_Float, "SPE_Utility", false);
			REGISTERFUNC(FindIf_String, "SPE_Utility", false);

			REGISTERFUNC(RemoveIf_Int, "SPE_Utility", false);
			REGISTERFUNC(RemoveIf_Float, "SPE_Utility", false);
			REGISTERFUNC(RemoveIf_String, "SPE_Utility", false);

			REGISTERFUNC(FilterArray_Form, "SPE_Utility", false);
			REGISTERFUNC(FilterArray_Int, "SPE_Utility", false);
			REGISTERFUNC(FilterArray_Float, "SPE_Utility", false);
			REGISTERFUNC(FilterArray_String, "SPE_Utility", false);

			REGISTERFUNC(PushFront_Int, "SPE_Utility", false);
			REGISTERFUNC(PushFront_Float, "SPE_Utility", false);
			REGISTERFUNC(PushFront_String, "SPE_Utility", false);
		}
	}

	namespace String
	{
		std::string ReplaceAt(STATICARGS, std::string a_str, int a_index, std::string a_replacement);

		inline void Register(VM* a_vm)
		{
			REGISTERFUNC(ReplaceAt, "SPE_Utility", false);
		}
	}

	inline bool Register(VM* a_vm)
	{
		Array::Register(a_vm);
		String::Register(a_vm);

		return true;
	}
}
