#pragma once

#include <type_traits>

namespace ddl
{
	constexpr size_t ct_strlen(const char* a)
	{
		size_t i = 0;
		while (a[i] != '\0') ++i;
		return i + 1;
	}

	// ct_string is heavily borrowed from hana & mpl string, i'm reimplementing it to avoid 
	// having dependencies
	template <char... Chrs>
	class ct_string
	{
	public:
		template <char... RhsChrs>
		constexpr bool operator== (const string<RhsChrs>&) const
		{
			return std::is_same_v<string<Chrs>, string<RhsChrs>>;
		}

		constexpr static const char value[] = { Chrs... };
	};

	template <const char* Str, size_t... Idx>
	constexpr auto apply_ct_string(std::index_sequence<Idx...>)
	{
		return ct_string<Str[Idx]...>{};
	}

	template <const char* Str>
	constexpr auto make_ct_string()
	{
		return apply_ct_string<Str>(std::make_index_sequence<ct_strlen(Str)>());
	}
}