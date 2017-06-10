#pragma once

#include <tuple>

namespace ddl
{
	template <typename Id, typename Export>
	struct export_info_t {};

	template <typename Export>
	struct export_t 
	{
		using type = Export;
	};

	struct export_not_found {};

	template <typename... Exports>
	struct exports_map;

	template <>
	struct exports_map<>
	{

		template <typename ExportId>
		constexpr static auto find_export(ExportId)
		{
			return export_t<export_not_found>{};
		}
	};

	template <typename Id, typename TExport, typename... Ids, typename... TExports>
	struct exports_map<export_info_t<Id, TExport>, export_info_t<Ids, TExports>...>
	{
		template <typename ExportId>
		constexpr static auto find_export(ExportId eid)
		{
			if constexpr(eid == Id{}) return export_t<TExport>{};
			else return exports_map<export_info_t<Ids, TExports>...>::find_export(eid);
		}
	};

	template <typename Export, typename Id>
	constexpr export_info_t<Id, Export> export_info(Id)
	{
		return {};
	}

	template <typename... Ids, typename... TExports>
	constexpr exports_map<export_info_t<Ids, TExports>...> make_export_map(export_info_t<Ids, TExports>...)
	{
		return {};
	}
}