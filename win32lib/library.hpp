#pragma once

#include <Windows.h>

#include <experimental\filesystem>

#include "decdynlib\basic_library.hpp"
#include "decdynlib\decdynlib\exports_map.hpp"
#include "decdynlib\decdynlib\string_export.hpp"
#include "decdynlib\decdynlib\ordinal_export.hpp"

namespace ddl
{
	// The win32 struct should have been a namespace but you can't use a namespace as template argument.
	struct win32
	{
		// The traits struct should have been a namespace but you can't define a reference inside a struct.
		struct traits
		{
			using handle_t = HMODULE;
			constexpr static const handle_t default_value = NULL;
			static handle_t load(const std::experimental::filesystem::path& lib_path);
			static void release(handle_t lib);

			template <typename ExportId>
			constexpr static bool is_expected_idetifier(ExportId)
			{
				constexpr auto id = ExportId::value;
				if constexpr (std::is_integral<decltype(id)>::value)
				{
					if constexpr (0 < id && (std::numeric_limits<uint16_t>::max)() >= id)
					{
						return true;
					}
				}
				else if constexpr (std::is_convertible<decltype(id), char const*>::value)
				{
					return true;
				}

				return false;
			}

			template <typename TId>
			static void* locate(handle_t lib, const TId& export_id)
			{
				return (void*)GetProcAddress(lib, (LPCSTR)export_id);
			}
		};

		template <typename ExportMap>
		static std::optional<basic_library<::ddl::win32, ExportMap>> 
		library(ExportMap, const std::experimental::filesystem::path& lib_path)
		{
			auto lib_handle = traits::load(lib_path);
			if (NULL == lib_handle) return {};
			else return basic_library<::ddl::win32, ExportMap>(lib_handle);
		}

	};
}