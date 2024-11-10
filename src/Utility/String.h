#pragma once

namespace String
{
	template <class T>
	constexpr void ApplyTransform(T& str, const std::function<int(int)>& a_func)
	{
		std::transform(str.cbegin(), str.cend(), str.begin(), a_func);
	}

	template <class T>
	constexpr void ToLower(T& str) { ApplyTransform(str, [](int c) { return std::tolower(c); }); }
	template <class T>
	constexpr void ToUpper(T& str) { ApplyTransform(str, [](int c) { return std::toupper(c); }); }

	// std::vector<std::string_view> Split(const std::string_view a_view, const char a_delim)
	// {
	// 	const auto trim = [&](size_t from, size_t len) {
	// 		auto word = a_view.substr(from, len);
	// 		while (!word.empty() && std::isspace(word[0]))
	// 			word.remove_prefix(1);
	// 		while (!word.empty() && std::isspace(word.back()))
	// 			word.remove_suffix(1);

	// 		return word;
	// 	};
	// 	std::vector<std::string_view> result;
	// 	size_t previous = 0;
	// 	for (size_t i = 0; i < a_view.size(); i++) {
	// 		if (a_view[i] != a_delim)
	// 			continue;

	// 		auto word = trim(previous, i - previous);
	// 		if (!word.empty()) {
	// 			result.push_back(word);
	// 		}
	// 		previous = i + 1;
	// 	}
	// 	if (auto last = trim(previous, std::string_view::npos); !last.empty()) {
	// 		result.push_back(last);
	// 	}
	// 	return result;
	// }

	inline std::string HexString(int a_num)
	{
		std::stringstream stream;
		stream << std::hex << a_num;
		std::string result(stream.str());
		ToUpper(result);
		return "0x" + result;
	}

} // namespace String
