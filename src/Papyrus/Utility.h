#pragma once

namespace Papyrus::Utility
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

			REGISTERFUNC(PushFront_Int, "SPE_Utility", false);
			REGISTERFUNC(PushFront_Float, "SPE_Utility", false);
			REGISTERFUNC(PushFront_String, "SPE_Utility", false);
		}
	}

	inline bool Register(VM* a_vm)
	{
		Array::Register(a_vm);

		return true;
	}
}
