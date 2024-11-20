#pragma once

namespace StringUtil
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

	inline std::vector<std::string_view> StringSplit(const std::string_view a_view, const char a_delim)
	{
		namespace views = std::ranges::views;
		return a_view | views::split(a_delim) | views::transform([](auto&& subrange) {
			auto word = std::string_view(&*subrange.begin(), std::ranges::distance(subrange));
			while (!word.empty() && std::isspace(word.front()))
				word.remove_prefix(1);
			while (!word.empty() && std::isspace(word.back()))
				word.remove_suffix(1);
			return word;
		}) | views::filter([](auto&& word) { return !word.empty(); }) | std::ranges::to<std::vector>();
	}

	inline std::vector<std::string> StringSplitToOwned(const std::string_view a_view, const char a_delim)
	{
		const auto ret = StringSplit(a_view, a_delim);
		return std::vector<std::string>(ret.cbegin(), ret.cend());
	}

}	 // namespace String
