#pragma once

#include <array>
#include <unordered_map>

namespace Color
{
	enum class Value
	{
		Red,
		Green,
		Yellow,
		Blue,
		Purple,
		Total,
		None,
		Grey
	};

	struct Name
	{
		static const std::array<std::string, 5> m_colorNames;
	};
}

