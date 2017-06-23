#pragma once

#include <utility>
#include <type_traits>

#include "DecDynLib\decdynlib\exports_map.hpp"

namespace ddl
{
	template <typename TChr, TChr... Chrs>
	struct _ct_string
	{
		constexpr static const TChr value[] = { Chrs..., TChr(0) };
	};

	namespace literals
	{
		template <typename TChr, TChr... Chrs>
		constexpr export_id<_ct_string<TChr, Chrs...>> operator"" _eid()
		{
			return {};
		}
	}
}