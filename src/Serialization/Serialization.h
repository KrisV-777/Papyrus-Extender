#pragma once

#undef min
#undef max

#include <frozen/string.h>

namespace Serialization
{
	static inline constexpr auto RecordID = 'scpe';
	constexpr frozen::string GetTypeName(uint32_t a_type);

	struct Serializer final
	{
		Serializer() = delete;

	public:
		enum : std::uint32_t
		{
			_Version = 1,

			_ActorHandler = 'achn',
		};

		static void SaveCallback(SKSE::SerializationInterface* a_intfc);
		static void LoadCallback(SKSE::SerializationInterface* a_intfc);
		static void RevertCallback(SKSE::SerializationInterface* a_intfc);
		static void FormDeleteCallback(RE::VMHandle a_handle);
	};

}	 // namespace Serialization
