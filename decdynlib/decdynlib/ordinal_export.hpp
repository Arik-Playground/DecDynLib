#pragma once

#include <cinttypes>
#include <type_traits>

#include "decdynlib\decdynlib\exports_map.hpp"

namespace ddl
{
	template <size_t Val>
	struct ordinal_id : public std::integral_constant<size_t, Val>
	{};

	namespace literals
	{

		template <size_t Val>
		constexpr auto _parse()
		{
			return export_id<ordinal_id<Val>>{};
		}

		template <size_t Val, char Head, char... Rest>
		constexpr auto _parse()
		{
			static_assert(
				Head >= '0' && Head <= '9',
				"Ordinal export can only be a decimal number");
			return _parse<(Val * 10) + (Head - '0'), Rest...>();
		}

		template <char... Chrs>
		constexpr auto operator"" _eid()
		{
			return _parse<0, Chrs...>();
		}
	}
}