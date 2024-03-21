#include "Utility.h"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <lua.hpp>

#include "Interface/CustomMenu.h"

namespace Papyrus::Utility
{
  namespace Array
  {
    template <typename T>
    void Shuffle(T& arr)
    {
			static std::mt19937 rng{ std::random_device{}() };
      std::ranges::shuffle(arr, rng);
		}
		void Shuffle_Int(RE::StaticFunctionTag*, RE::reference_array<int> arr) { Shuffle(arr); }
		void Shuffle_Float(RE::StaticFunctionTag*, RE::reference_array<float> arr) { Shuffle(arr); }
		void Shuffle_String(RE::StaticFunctionTag*, RE::reference_array<RE::BSFixedString> arr) { Shuffle(arr); }

		template <typename T>
		bool Sort(VM* a_vm, StackID a_stackID, T& arr, const std::string& code)
		{
			try {
				sol::state lua{};
				const auto success = lua.script(code);
				std::stable_sort(arr.begin(), arr.end(), [&](auto a, auto b) -> bool {
					if constexpr (std::is_same_v<T, RE::reference_array<RE::BSFixedString>>) {
						std::string a_{ a.data() };
						std::string b_{ b.data() };
						bool ret = lua["compare"](a_, b_);
						return ret;
					} else {
						bool ret = lua["compare"](a, b);
						return ret;
					}
				});
				return true;
			} catch (const std::exception& e) {
				a_vm->TraceStack(fmt::format("Invalid Lua Code, Error: {}", e.what()).c_str(), a_stackID);
				return false;
			}
		}
		bool Sort_Int(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<int> arr, std::string lua) { return Sort(a_vm, a_stackID, arr, lua); }
		bool Sort_Float(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<float> arr, std::string lua) { return Sort(a_vm, a_stackID, arr, lua); }
		bool Sort_String(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<RE::BSFixedString> arr, std::string lua) { return Sort(a_vm, a_stackID, arr, lua); }

		template <typename T>
		int32_t FindIf(VM* a_vm, StackID a_stackID, T& arr, const std::string& code)
		{
			try {
				sol::state lua{};
				const auto success = lua.script(code);
				const auto where = std::find_if(arr.begin(), arr.end(), [&](auto a) -> bool {
					if constexpr (std::is_same_v<T, RE::reference_array<RE::BSFixedString>>) {
						std::string a_{ a.data() };
						bool ret = lua["predicate"](a_);
						return ret;
					} else {
						bool ret = lua["predicate"](a);
						return ret;
					}
				});
				return where == arr.end() ? -1 : static_cast<int32_t>(std::ptrdiff_t(std::distance(arr.begin(), where)));
			} catch (const std::exception& e) {
				a_vm->TraceStack(fmt::format("Invalid Lua Code, Error: {}", e.what()).c_str(), a_stackID);
				return -2;
			}
		}
		int32_t FindIf_Int(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<int> arr, std::string lua) { return FindIf(a_vm, a_stackID, arr, lua); }
		int32_t FindIf_Float(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<float> arr, std::string lua) { return FindIf(a_vm, a_stackID, arr, lua); }
		int32_t FindIf_String(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<RE::BSFixedString> arr, std::string lua) { return FindIf(a_vm, a_stackID, arr, lua); }

		std::vector<int> PushFrontInt(RE::StaticFunctionTag*, std::vector<int> arr, int val)
    {
      arr.insert(arr.begin(), val);
      return arr;
    }
		std::vector<bool> PushFrontBool(RE::StaticFunctionTag*, std::vector<bool> arr, bool val)
    {
      arr.insert(arr.begin(), val);
      return arr;
    }
		std::vector<float> PushFrontFloat(RE::StaticFunctionTag*, std::vector<float> arr, float val)
    {
      arr.insert(arr.begin(), val);
      return arr;
    }
		std::vector<RE::BSFixedString> PushFrontString(RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, RE::BSFixedString val)
    {
      arr.insert(arr.begin(), val);
      return arr;
    }
	}

	namespace Interface
	{
		void PrintConsole(RE::StaticFunctionTag*, RE::BSFixedString a_msg)
		{
			RE::ConsoleLog::GetSingleton()->Print(a_msg.c_str());
		}

		bool OpenCustomMenu(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::string_view a_filepath)
		{
			if (a_filepath.empty()) {
				a_vm->TraceStack("File path to swf file is empty", a_stackID);
				return false;
			} else if (!fs::exists(fmt::format("Data\\Interface\\{}.swf", a_filepath))) {
				a_vm->TraceStack("File path does not lead to a valid file", a_stackID);
				return false;
			}			

			if (Internal::Interface::CustomMenu::IsOpen()) {
				return false;
			}

			Internal::Interface::CustomMenu::SetSwfPath(a_filepath);
			Internal::Interface::CustomMenu::Show();
			return true;
		}

		void CloseCustomMenu(RE::StaticFunctionTag*)
		{
			Internal::Interface::CustomMenu::Hide();
		}

	}
}