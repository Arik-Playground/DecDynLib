#pragma once

#include <utility>
#include <type_traits>

namespace ddl
{
	template <typename TChr, TChr... Chrs>
	struct _ct_string
	{
		constexpr static const TChr value[] = { Chrs... };
	};

	template <typename TChrA, TChrA... ChrsA, typename TRhs>
	constexpr bool operator==(_ct_string<TChrA, ChrsA...> a, TRhs)
	{
		return std::is_same<decltype(a), TRhs>{};
	}

	namespace literals
	{
		template <typename TChr, TChr... Chrs>
		constexpr _ct_string<TChr, Chrs...> operator"" _eid()
		{
			return {};
		}
	}
}