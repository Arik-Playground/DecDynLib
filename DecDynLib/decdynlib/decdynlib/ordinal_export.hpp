#pragma once

#include <cinttypes>
#include <type_traits>

#include "decdynlib/decdynlib/type_map.hpp"

template <typename T, T Ordinal, typename TExport>
struct ddl::export_info<T, Ordinal, std::enable_if_t<(std::_Is_integral<T>::value), TExport>>
{
	static_assert(os::Windows == os_type, "Ordinal export isn't available to this OS");
	constexpr if (os::Windows == os_type)
	{
		static_assert(
			(Ordinal >= 0)		&& 
			(Ordinal <= 0xffff), 
			"Invalid ordinal value for Windows");

		using ordinal_t = uint32_t;
	}

	using identifier = std::integral_constant<ordinal_t, Ordinal>;
	using export_t = TExport;
};