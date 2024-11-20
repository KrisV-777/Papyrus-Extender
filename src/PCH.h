#pragma once

#pragma warning(push)
#pragma warning(disable : 4200)
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#pragma warning(pop)

#include <atomic>
#include <unordered_map>
#include <unordered_set>

#pragma warning(push)
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#pragma warning(pop)

namespace logger = SKSE::log;
namespace fs = std::filesystem;
using namespace std::literals;

#include <magic_enum.hpp>
static_assert(magic_enum::is_magic_enum_supported, "magic_enum is not supported");

#include "Util/Random.h"
#include "Util/Singleton.h"

#define REL_ID(se, ae) REL::RelocationID(se, ae)
#define REL_OF(se, ae, vr) REL::VariantOffset(se, ae, vr)

namespace stl
{
	using namespace SKSE::stl;
	
	template <class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		auto& trampoline = SKSE::GetTrampoline();
		SKSE::AllocTrampoline(14);

		T::func = trampoline.write_call<5>(a_src, T::thunk);
	}

	template <class F, class T>
	void write_vfunc()
	{
		REL::Relocation<std::uintptr_t> vtbl{ F::VTABLE[0] };
		T::func = vtbl.write_vfunc(T::size, T::thunk);
	}

	inline bool read_string(SKSE::SerializationInterface* a_intfc, std::string& a_str)
	{
		std::size_t size = 0;
		if (!a_intfc->ReadRecordData(size)) {
			return false;
		}
		a_str.resize(size);
		if (!a_intfc->ReadRecordData(a_str.data(), static_cast<std::uint32_t>(size))) {
			return false;
		}
		return true;
	}

	template <class S>
	inline bool write_string(SKSE::SerializationInterface* a_intfc, const S& a_str)
	{
		std::size_t size = a_str.length() + 1;
		return a_intfc->WriteRecordData(size) && a_intfc->WriteRecordData(a_str.data(), static_cast<std::uint32_t>(size));
	}
}

namespace Papyrus
{
#define REGISTERFUNC(func, classname, delay) a_vm->RegisterFunction(#func##sv, classname, func, !delay)
#define STATICARGS VM *a_vm, RE::VMStackID a_stackID, RE::StaticFunctionTag *
#define TRACESTACK(err) a_vm->TraceStack(err, a_stackID)

	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
}

namespace Serialization
{
	constexpr std::string GetTypeName(uint32_t a_type)
	{
		const char ret[4]{
			static_cast<char>(a_type & 0xff),
			static_cast<char>((a_type >> 8) & 0xff),
			static_cast<char>((a_type >> 16) & 0xff),
			static_cast<char>((a_type >> 24) & 0xff)
		};
		return std::string{ ret, 4 };
	}
}

#define DLLEXPORT __declspec(dllexport)
