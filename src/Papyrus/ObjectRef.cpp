#include "ObjectRef.h"

namespace Papyrus::ObjectRef
{
	std::vector<RE::TESObjectREFR*> GetContainer(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESForm* a_form)
	{
		using BSTSize = RE::BSTArrayBase::size_type;
		if (!a_form) {
			a_vm->TraceStack("Form is none", a_stackID);
			return {};
		}
		const auto data = RE::TESDataHandler::GetSingleton();
		auto& refs = data->formArrays[static_cast<size_t>(RE::FormType::Reference)];
    const auto fn = static_cast<float>(refs.size());
		const auto tcount = std::ceil(std::sqrt(fn));
		const auto pert = static_cast<BSTSize>(std::ceil(fn / tcount));
		std::vector<std::thread> threads{};
		threads.reserve(static_cast<size_t>(tcount));
		std::vector<RE::TESObjectREFR*> ret{};
		std::mutex _m{};
		for (BSTSize i = 0; i < refs.size(); i += pert) {
			auto end = static_cast<BSTSize>(std::min<size_t>(refs.size(), i + pert));
			threads.emplace_back([&refs, &a_form, &_m, &ret, i, end]() {
				for (BSTSize n = i; n < end; n++) {
					auto obj = refs[n]->As<RE::TESObjectREFR>();
					if (!obj)
						continue;

					auto inv = obj->GetInventory([&a_form](RE::TESBoundObject& it) { return it.formID == a_form->formID; }, true);
					if (!inv.empty()) {
						_m.lock();
						ret.push_back(obj);
						_m.unlock();
					}
				}
			});
		}
		for (auto&& t : threads) {
			t.join();
		}
		return ret;
	}

}	 // namespace Papyrus::ObjectRef
