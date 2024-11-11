#pragma once

namespace Utility
{
#define STR_TRANSFORM(f) std::transform(str.cbegin(), str.cend(), str.begin(), [](int c) { return f(c); });

	template <class T>
	constexpr void ToLower(T& str)
	{
		STR_TRANSFORM(std::tolower)
	}
	template <class T>
	constexpr void ToUpper(T& str)
	{
		STR_TRANSFORM(std::toupper)
	}

#undef STR_TRANSFORM

	inline std::string HexString(int a_num)
	{
		return std::format("0x{:X}", a_num);
	}

	inline std::vector<std::string_view> StringSplit(const std::string_view a_view, const char a_delim)
	{
		const auto trim = [&](size_t from, size_t len) {
			auto word = a_view.substr(from, len);
			while (!word.empty() && std::isspace(word[0]))
				word.remove_prefix(1);
			while (!word.empty() && std::isspace(word.back()))
				word.remove_suffix(1);
			return word;
		};
		std::vector<std::string_view> result;
		size_t previous = 0;
		for (size_t i = 0; i < a_view.size(); i++) {
			if (a_view[i] != a_delim)
				continue;
			auto word = trim(previous, i - previous);
			if (!word.empty()) {
				result.push_back(word);
			}
			previous = i + 1;
		}
		if (auto last = trim(previous, std::string_view::npos); !last.empty()) {
			result.push_back(last);
		}
		return result;
	}

}	 // namespace String
