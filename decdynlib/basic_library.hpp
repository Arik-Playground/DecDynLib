#pragma once

#include <optional>
#include <experimental\filesystem>

#include "decdynlib\decdynlib\exports_map.hpp"

namespace ddl
{
	template <typename Platform, typename ExportMap>
	class basic_library
	{
		using handle_t = typename Platform::traits::handle_t;

	public:
		basic_library() = delete;
		basic_library(const basic_library& other) = delete;
		basic_library(basic_library&& other) :
		m_lib(other.m_lib)
		{
			other.m_lib = Platform::traits::default_value;
		}

		basic_library& operator= (basic_library other)
		{
			std::swap(this->m_lib, other.m_lib);
			return *this;
		}

		~basic_library()
		{
			if (Platform::traits::default_value != m_lib) Platform::traits::release(m_lib);
		}

		template <typename Id>
		auto operator[] (Id export_id) const
		{
			static_assert(
				Platform::traits::is_expected_idetifier(export_id),
				"Unexpected identifier");

			auto export_type = ExportMap::find_export(export_id);
			static_assert(
				export_type != type_t<export_not_found>{},
				"Export not found.");

			// Returning a pointer because there is no such thing ref optional
			return reinterpret_cast<typename decltype(export_type)::type*>(
				Platform::traits::locate(m_lib, Id::value));
		}

	private:
		friend Platform;

		basic_library (handle_t lib) :
		m_lib(lib)
		{}

		handle_t m_lib = Platform::traits::default_value;
	};
}
