#pragma once

#include "Papyrus/ObjectRef.h"
#include "StringUtil.h"

namespace Registry::Console
{
	inline void PrintConsole(std::string_view a_msg) { RE::ConsoleLog::GetSingleton()->Print(a_msg.data()); }
	inline void PrintConsole(const char* a_msg) { RE::ConsoleLog::GetSingleton()->Print(a_msg); }
	template <typename... Args>
	inline void PrintConsole(fmt::format_string<Args...> a_fmt, Args&&... args)
	{
		const auto msg = fmt::format(a_fmt, std::forward<Args>(args)...);
		RE::ConsoleLog::GetSingleton()->Print(msg.data());
	}

	template <typename T>
	static T FormFromString(const std::string_view a_string, int base)
	{
		const auto split = a_string.find("|");
		const auto formid = std::stoi(a_string.substr(0, split).data(), nullptr, base);
		if (split == std::string_view::npos) {
			if constexpr (std::is_same<T, RE::FormID>::value) {
				return formid;
			} else {
				static_assert(std::is_pointer<T>::value);
				using U = std::remove_pointer<T>::type;
				return RE::TESForm::LookupByID<U>(formid);
			}
		}

		const auto esp = a_string.substr(split + 1);
		if constexpr (std::is_same<T, RE::FormID>::value) {
			return RE::TESDataHandler::GetSingleton()->LookupFormID(formid, esp);
		} else {
			static_assert(std::is_pointer<T>::value);
			using U = std::remove_pointer<T>::type;
			return RE::TESDataHandler::GetSingleton()->LookupForm<U>(formid, esp);
		}
	}
	template <typename T>
	static T FormFromString(const std::string_view a_string)
	{
		const int base = a_string.starts_with("0x") ? 16 : 10;
		return FormFromString<T>(a_string, base);
	}

	struct CompileAndRun
	{
		static void thunk(RE::Script* a_script, RE::ScriptCompiler* a_compiler, RE::COMPILER_NAME a_name, RE::TESObjectREFR* a_targetRef)
		{
			std::string cmd{ a_script->GetCommand() };
			String::ToLower(cmd);
			if (!cmd.starts_with("scrab")) {
				return func(a_script, a_compiler, a_name, a_targetRef);
			}

			PrintConsole("Invalid command");
		}
		static inline REL::Relocation<decltype(thunk)> func;
	};

	inline void Install()
	{
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(52065, 52952), OFFSET(0xE2, 0x52) };
		stl::write_thunk_call<CompileAndRun>(target.address());

		logger::info("Registered Console Integration");
	}
}
