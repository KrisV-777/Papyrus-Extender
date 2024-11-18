#include "Serialization.h"

#include "Data/ActorManager.h"

namespace Serialization
{
	constexpr frozen::string GetTypeName(uint32_t a_type)
	{
		const char ret[4] {
			static_cast<char>(a_type & 0xff),
			static_cast<char>((a_type >> 8) & 0xff),
			static_cast<char>((a_type >> 16) & 0xff),
			static_cast<char>((a_type >> 24) & 0xff)
		};
		return frozen::string{ ret, 4 };
	}

	void Serializer::SaveCallback(SKSE::SerializationInterface* a_intfc)
	{
#define SAVE(type, func)                                                              \
	if (!a_intfc->OpenRecord(type, _Version))                                           \
		logger::error("Failed to open record {}", std::string_view{ GetTypeName(type) }); \
	else                                                                                \
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
			const auto typestr = std::string_view{ GetTypeName(type) };
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
				logger::warn("Unrecognized type: {}", typestr);
				break;
			}
		}
	}

	void Serializer::RevertCallback(SKSE::SerializationInterface* a_intfc)
	{
		Data::ActorManager::GetSingleton()->Revert(a_intfc);
	}

	void Serializer::FormDeleteCallback(RE::VMHandle)	{}

}	 // namespace Serialization
