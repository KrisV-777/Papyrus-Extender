#pragma once

namespace String
{
	template <class T>
	constexpr void ToLower(T& str)
	{
		std::transform(str.cbegin(), str.cend(), str.begin(), [](unsigned char c) { return static_cast<unsigned char>(std::tolower(c)); });
	}

	std::vector<std::string_view> Split(const std::string_view a_view, const char a_delim)
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
} // namespace String
