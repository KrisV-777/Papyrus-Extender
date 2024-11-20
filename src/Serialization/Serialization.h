#pragma once

namespace Serialization
{
	static inline constexpr auto RecordID = 'scpe';

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
