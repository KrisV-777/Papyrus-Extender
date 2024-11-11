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
#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif
#pragma warning(pop)

namespace logger = SKSE::log;
namespace fs = std::filesystem;
using namespace std::literals;

#include <magic_enum.hpp>
static_assert(magic_enum::is_magic_enum_supported, "magic_enum is not supported");

#include "Random.h"
#include "Singleton.h"

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

}

namespace Papyrus
{
#define REGISTERFUNC(func, classname, delay) a_vm->RegisterFunction(#func##sv, classname, func, !delay)
#define STATICARGS VM *a_vm, RE::VMStackID a_stackID, RE::StaticFunctionTag *
#define TRACESTACK(err) a_vm->TraceStack(err, a_stackID)

	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
}

#define DLLEXPORT __declspec(dllexport)
