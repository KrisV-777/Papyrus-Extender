#include "Utility.h"

#define SOL_ALL_SAFETIES_ON 1
#include <lua.hpp>
#include <sol/sol.hpp>

#include "Utility/Keywords.h"

namespace Papyrus::Util
{
	inline std::optional<sol::state> OpenLua(const std::string& code)
	{
		sol::state lua{};
		auto success = [&]() mutable {
			if (code.ends_with(".lua")) {
				if (!fs::exists(code)) {
					throw std::exception(std::format("No file at path {}", code).c_str());
				}
				const auto res = lua.script_file(code);
				return res.valid();
			}
			return lua.script(code).valid();
		}();
		if (success)
			return lua;
		return std::nullopt;
	}

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
				auto lua = OpenLua(code);
				if (!lua)
					return false;
				std::stable_sort(arr.begin(), arr.end(), [&](auto a, auto b) -> bool {
					if constexpr (std::is_same_v<T, RE::reference_array<RE::BSFixedString>>) {
						bool ret = (*lua)["compare"](a.data(), b.data());
						return ret;
					} else {
						bool ret = (*lua)["compare"](a, b);
						return ret;
					}
				});
				return true;
			} catch (const std::exception& e) {
				a_vm->TraceStack(std::format("Invalid Lua Code, Error: {}", e.what()).c_str(), a_stackID);
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
				auto lua = OpenLua(code);
				if (!lua)
					return -2;
				const auto where = std::find_if(arr.begin(), arr.end(), [&](auto a) -> bool {
					if constexpr (std::is_same_v<T, RE::reference_array<RE::BSFixedString>>) {
						bool ret = (*lua)["predicate"](a.data());
						return ret;
					} else {
						bool ret = (*lua)["predicate"](a);
						return ret;
					}
				});
				return where == arr.end() ? -1 : static_cast<int32_t>(std::ptrdiff_t(std::distance(arr.begin(), where)));
			} catch (const std::exception& e) {
				a_vm->TraceStack(std::format("Invalid Lua Code, Error: {}", e.what()).c_str(), a_stackID);
				return -2;
			}
		}
		int32_t FindIf_Int(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<int> arr, std::string lua) { return FindIf(a_vm, a_stackID, arr, lua); }
		int32_t FindIf_Float(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<float> arr, std::string lua) { return FindIf(a_vm, a_stackID, arr, lua); }
		int32_t FindIf_String(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::reference_array<RE::BSFixedString> arr, std::string lua) { return FindIf(a_vm, a_stackID, arr, lua); }

		template <typename T, typename V>
		T PushFront(T& arr, V val)
		{
			arr.insert(arr.begin(), val);
			return arr;
		}
		std::vector<int> PushFront_Int(RE::StaticFunctionTag*, std::vector<int> arr, int val) { return PushFront(arr, val); }
		std::vector<float> PushFront_Float(RE::StaticFunctionTag*, std::vector<float> arr, float val) { return PushFront(arr, val); }
		std::vector<RE::BSFixedString> PushFront_String(RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, RE::BSFixedString val) { return PushFront(arr, val); }

		template <typename T>
		T RemoveIf(VM* a_vm, StackID a_stackID, T& arr, const std::string& code)
		{
			try {
				if (auto lua = OpenLua(code)) {
					std::erase_if(arr, [&](auto it) {
						if constexpr (std::is_same_v<T, RE::reference_array<RE::BSFixedString>>) {
							bool ret = (*lua)["predicate"](it.data());
							return ret;
						} else {
							bool ret = (*lua)["predicate"](it);
							return ret;
						}
					});
				}
			} catch (const std::exception& e) {
				a_vm->TraceStack(std::format("Invalid Lua Code, Error: {}", e.what()).c_str(), a_stackID);
			}
			return arr;
		}
		std::vector<int> RemoveIf_Int(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<int> arr, std::string lua) { return RemoveIf(a_vm, a_stackID, arr, lua); }
		std::vector<float> RemoveIf_Float(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<float> arr, std::string lua) { return RemoveIf(a_vm, a_stackID, arr, lua); }
		std::vector<RE::BSFixedString> RemoveIf_String(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, std::string lua) { return RemoveIf(a_vm, a_stackID, arr, lua); }

		template <typename T>
		T FilterArray(T& arr, T& filter)
		{
			std::erase_if(arr, [&](auto it) { return std::ranges::contains(filter, it); });
			return arr;
		}
		std::vector<RE::TESForm*> FilterArray_Form(RE::StaticFunctionTag*, std::vector<RE::TESForm*> arr, std::vector<RE::TESForm*> filter) { return FilterArray(arr, filter); }
		std::vector<int> FilterArray_Int(RE::StaticFunctionTag*, std::vector<int> arr, std::vector<int> filter) { return FilterArray(arr, filter); }
		std::vector<float> FilterArray_Float(RE::StaticFunctionTag*, std::vector<float> arr, std::vector<float> filter) { return FilterArray(arr, filter); }
		std::vector<RE::BSFixedString> FilterArray_String(RE::StaticFunctionTag*, std::vector<RE::BSFixedString> arr, std::vector<RE::BSFixedString> filter) { return FilterArray(arr, filter); }

  	std::vector<RE::TESForm*> FilterFormsByKeyword(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, std::vector<RE::BGSKeyword*> a_keywords, bool a_matchall, bool a_invert)
		{
			std::vector<RE::TESForm*> filtered;
			for (const auto& form : a_forms) {
				if (!form)
					continue;
				if (Utility::HasKeywords(form, a_keywords, a_matchall) != a_invert) {
					filtered.push_back(form);
				}
			}
			return filtered;
		}

		std::vector<RE::TESForm*> FilterFormsByGoldValue(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, int a_value, bool a_greater, bool a_equal)
		{
			std::vector<RE::TESForm*> filtered;
			for (const auto& form : a_forms) {
				if (!form)
					continue;
				const auto cmp = form->GetGoldValue() <=> a_value;
				if (cmp > 0 && a_greater) {
					filtered.push_back(form);
				} else if (cmp < 0 && !a_greater) {
					filtered.push_back(form);
				} else if (cmp == 0 && a_equal) {
					filtered.push_back(form);
				}
			}
			return filtered;
		}

		std::vector<RE::TESObjectARMO*> FilterBySlot(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, std::vector<int> a_slots, bool a_all)
		{
			const auto slotmask = std::accumulate(a_slots.begin(), a_slots.end(), 0u, [](auto acc, auto b) { return acc | (b - 30); });
			return FilterBySlotmask(nullptr, a_forms, slotmask, a_all);
		}

		std::vector<RE::TESObjectARMO*> FilterBySlotmask(RE::StaticFunctionTag*, std::vector<RE::TESForm*> a_forms, uint32_t a_slotmask, bool a_all)
		{
			std::vector<RE::TESObjectARMO*> filtered;
			for (const auto& form : a_forms) {
				const auto armor = form ? form->As<RE::TESObjectARMO>() : nullptr;
				if (!armor)
					continue;
				const auto slotmask = static_cast<uint32_t>(armor->GetSlotMask());
				const auto res = slotmask & a_slotmask;
				if (a_all && res == a_slotmask) {
					filtered.push_back(armor);
				} else if (!a_all && res > 0) {
					filtered.push_back(armor);
				}
			}
			return filtered;
		}

	}	// namespace Array
} // namespace Papyrus::Utility
