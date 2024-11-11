#pragma once

namespace Serialization
{
	class Serialize
	{
	public:
		static inline const auto RecordID = _byteswap_ulong('scpe');

		static void Save(SKSE::SerializationInterface* a_intfc);
		static void Load(SKSE::SerializationInterface* a_intfc);
		static void Revert(SKSE::SerializationInterface* a_intfc);
	};
}	 // namespace Serialization
