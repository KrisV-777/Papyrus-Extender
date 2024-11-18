#pragma once

namespace Serialization
{
	template <typename T>
	inline void LoadFormIDs(SKSE::SerializationInterface* a_intfc, T& a_set)
	{
		static_assert(std::is_same_v<RE::FormID, typename T::value_type>);
		size_t num;
		a_intfc->ReadRecordData(num);
		a_set.clear();
		for (size_t i = 0; i < num; i++) {
			typename T::value_type value;
			a_intfc->ReadRecordData(value);
			if (!a_intfc->ResolveFormID(value, value)) {
				logger::warn("Failed to resolve FormID ({:X})", value);
				continue;
			}
			a_set.insert(value);
		}
	}

	template <typename T>
	inline void SaveFormIDs(SKSE::SerializationInterface* a_intfc, const T& a_set)
	{
		static_assert(std::is_same_v<RE::FormID, typename T::value_type>);
		a_intfc->WriteRecordData(a_set.size());
		for (const auto& value : a_set) {
			a_intfc->WriteRecordData(value);
		}
	}
} // namespace Serialization
