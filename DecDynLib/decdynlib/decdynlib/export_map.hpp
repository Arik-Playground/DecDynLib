#pragma once

#include <cinttypes>
#include <type_traits>

#include "decdynlib/decdynlib/os_info.hpp"

namespace ddl
{
	template <typename TIdentifier, TIdentifier Identifier, typename TExport>
	struct export_info;

	template <typename... TExports>
	struct export_map;

	template <typename TIdentifier, TIdentifiers Identifier>
	struct export_not_found_tag;
}

template <
	typename TIdentifier, 
	TIdentifiers Identifier, 
	typename TExport, 
	typename... TIdentifiers, 
	TIdentifiers... Identifiers, 
	typename... TExports>
struct ddl::export_map<export_info<TIdentifier, Identifier, TExport>, export_info<TIdentifiers, Identifiers, TExports>...>
{
	template <typename TRhsIdentifier, TRhsIdentifier RhsIdentifier>
	using locate_export =
		std::conditional_t < (export_info<TIdentifier, Identifier, TExport>::identifier{} == export_info<TRhsIdentifier, RhsIdentifier, void>::identifier{}),
		TExport,
		export_map<export_info<TIdentifiers, Identifiers, TExports>...>::locate_export<TRhsIdentifier, RhsIdentifier>>;
};

template <>
struct ddl::export_map<>
{
	template <typename TRhsIdentifier, TRhsIdentifier RhsIdentifier>
	using locate_export = export_not_found_tag<TRhsIdentifier, RhsIdentifier>;
};