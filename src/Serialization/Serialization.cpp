#include "Serialization.h"

#include "Data/ActorManager.h"
#include "Papyrus/Events/EventManager.h"

namespace Serialization
{
	void Serializer::SaveCallback(SKSE::SerializationInterface* a_intfc)
	{
		Papyrus::Events::EventManager::GetSingleton()->Save(a_intfc, _Version);

#define SAVE(type, func)                                          \
	if (!a_intfc->OpenRecord(type, _Version))                       \
		logger::error("Failed to open record {}", GetTypeName(type)); \
	else                                                            \
		func(a_intfc);

		SAVE(_ActorHandler, Data::ActorManager::GetSingleton()->Save);

#undef SAVE
	}

	void Serializer::LoadCallback(SKSE::SerializationInterface* a_intfc)
	{
		uint32_t type;
		uint32_t version;
		uint32_t length;
		while (a_intfc->GetNextRecordInfo(type, version, length)) {
			const auto typestr = GetTypeName(type);
			if (version != _Version) {
				logger::info("Invalid Version for loaded Data of Type = {}. Expected = {}; Got = {}", typestr, std::to_underlying(_Version), version);
				continue;
			}
			logger::info("Loading Data of Type: {}", typestr);
			switch (type) {
			case _ActorHandler:
				Data::ActorManager::GetSingleton()->Load(a_intfc);
				break;
			default:
				Papyrus::Events::EventManager::GetSingleton()->Load(a_intfc, type);
				break;
			}
		}
	}

	void Serializer::RevertCallback(SKSE::SerializationInterface* a_intfc)
	{
		Papyrus::Events::EventManager::GetSingleton()->Revert(a_intfc);
		Data::ActorManager::GetSingleton()->Revert(a_intfc);
	}

	void Serializer::FormDeleteCallback(RE::VMHandle a_handle)
	{
		Papyrus::Events::EventManager::GetSingleton()->FormDelete(a_handle);
	}

}	 // namespace Serialization
