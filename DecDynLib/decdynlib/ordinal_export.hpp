#pragma once

#include <cinttypes>
#include <type_traits>

template <uint32_t Identifier, typename TExport>
struct ddl::export_info<uint32_t, Identifier, TExport>
{
	static_assert(os::Windows == os_type, "Only Windows supports ordinal exports");

	using identifier = std::integral_constant<uint32_t, Identifier>;
	using export_t = TExport;
};