#pragma once

#include <cinttypes>
#include <type_traits>

namespace ddl
{
	namespace literals
	{

		template <uint16_t val = 0>
		constexpr auto _parse()
		{
			return std::integral_constant<uint16_t, val>{};
		}

		template <uint16_t val = 0, char Head, char... Rest>
		constexpr auto _parse()
		{
			return _parse<Rest..., (val * 10) + (Head & 1111)>();
		}

		template <char... Chrs>
		constexpr auto operator"" _eid()
		{
			return _parse<Chrs...>();
		}
	}
}