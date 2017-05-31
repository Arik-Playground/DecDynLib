#pragma once

#include <cinttypes>
#include <type_traits>

#include "DecDynLib/decdynlib/os_info"

namespace ddl
{
	template <typename... exports>
	class export_map
	{

	};

	template <typename TIdentifier, TIdentifier>
	struct export_info 
	{
		// Crashing the compiler when trying to define an export that has no specialization.
		static_assert(sizeof(T) == 0, "A valid export info of type T was not found");
	};
}
