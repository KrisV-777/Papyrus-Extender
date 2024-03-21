#pragma once

namespace Papyrus
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

		std::vector<int> PushFrontInt(RE::StaticFunctionTag*, std::vector<int> arr, int push);
		std::vector<bool> PushFrontBool(RE::StaticFunctionTag*, std::vector<bool> arr, bool push);
		std::vector<float> PushFrontFloat(RE::StaticFunctionTag*, std::vector<float> arr, float push);
		std::vector<RE::BSFixedString> PushFrontString(RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, RE::BSFixedString push);

		inline void Register(VM* a_vm){
      REGISTERFUNC(Shuffle_Int, "SPE_Utility");
      REGISTERFUNC(Shuffle_Float, "SPE_Utility");
      REGISTERFUNC(Shuffle_String, "SPE_Utility");

      REGISTERFUNC(Sort_Int, "SPE_Utility");
      REGISTERFUNC(Sort_Float, "SPE_Utility");
      REGISTERFUNC(Sort_String, "SPE_Utility");

			REGISTERFUNC(FindIf_Int, "SPE_Utility");
			REGISTERFUNC(FindIf_Float, "SPE_Utility");
			REGISTERFUNC(FindIf_String, "SPE_Utility");

			REGISTERFUNC(PushFrontInt, "SPE_Utility");
      REGISTERFUNC(PushFrontBool, "SPE_Utility");
      REGISTERFUNC(PushFrontFloat, "SPE_Utility");
      REGISTERFUNC(PushFrontString, "SPE_Utility");
		};
	};

  namespace Interface
	{
		void PrintConsole(RE::StaticFunctionTag*, RE::BSFixedString a_msg);
		bool OpenCustomMenu(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::string_view a_filepath);
		void CloseCustomMenu(RE::StaticFunctionTag*);

		inline void Register(VM* a_vm)
		{
			REGISTERFUNC(PrintConsole, "SPE_Utility");
			REGISTERFUNC(OpenCustomMenu, "SPE_Utility");
			REGISTERFUNC(CloseCustomMenu, "SPE_Utility");
		};
	};

	inline bool Register(VM* a_vm)
	{
		Array::Register(a_vm);
		Interface::Register(a_vm);

		return true;
	};
}
