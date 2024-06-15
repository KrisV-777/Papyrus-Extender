#include "Form.h"

namespace Papyrus::Form
{
	std::vector<RE::TESObjectREFR*> GetContainer(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm->TraceStack("Form is none", a_stackID);
			return {};
		}
		std::vector<RE::TESObjectREFR*> objects{};
		{
			const auto& [map, lock] = RE::TESForm::GetAllForms();
			const RE::BSReadWriteLock l{ lock };
			if (!map) {
				return {};
			}
			objects.reserve(map->size() / 32);
			for (auto&& [id, obj] : *map) {
				auto asref = obj->As<RE::TESObjectREFR>();
				if (!asref)
					continue;
				objects.push_back(asref);
			}
		}
		const auto fsize = static_cast<float>(objects.size());
		const auto thread_count = std::ceil(std::sqrt(fsize));
		const auto per_thread = static_cast<size_t>(std::ceil(fsize / thread_count));
		std::vector<RE::TESObjectREFR*> ret{};
		std::vector<std::thread> threads{};
		threads.reserve(static_cast<size_t>(thread_count));
		std::mutex _m{};

		auto refform = a_form->AsReference();
		auto baseform = refform ? refform->GetBaseObject() : nullptr;
		auto lookup = baseform ? baseform->GetFormID() : a_form->formID;

		for (size_t i = 0; i < objects.size(); i += per_thread) {
			auto end = std::min<size_t>(objects.size(), i + per_thread);
			threads.emplace_back([&, i, end]() {
				for (size_t n = i; n < end; n++) {
					auto inv = objects[n]->GetInventory([&](RE::TESBoundObject& it) { return it.formID == lookup; }, true);
					if (inv.empty())
						continue;
					if (!refform) {
						// looking for general object
						_m.lock();
						ret.push_back(objects[n]);
						_m.unlock();
					} else {
						// looking for discrete ref
						for (auto&& [obj, data] : inv) {
							auto extras = data.second->extraLists;
							if (!extras)
								continue;
							for (auto&& extra : *extras) {
								auto extraref = extra->GetByType<RE::ExtraReferenceHandle>();
								if (!extraref)
									continue;
								auto ref = extraref->containerRef.get();
								if (!ref)
									continue;
								if (ref->formID == refform->formID) {
									_m.lock();
									ret.push_back(objects[n]);
									_m.unlock();
									break;
								}
							}
						}
					}
				}
			});
		}
		for (auto&& t : threads) {
			t.join();
		}
		return ret;
	}

}	 // namespace Papyrus::Form
