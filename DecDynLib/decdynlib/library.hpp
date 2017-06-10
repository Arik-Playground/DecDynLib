#pragma once

#include <experimental\filesystem>

#include <decdynlib\decdynlib\export_map.hpp>

namespace ddl
{
	template <typename LibraryTraits, typename ExportMap>
	class library
	{
		using LibraryTraits::handle_t;
		using std::experimental::filesystem::path;

	public:
		library explicit (const path& lib_path)
		m_path(lib_path),
		m_lib(LibraryTraits::load(m_path))
		{}
	
		library() = delete;

		library(const library& other) :
		m_path(other.m_path),
		m_lib(LibraryTraits::load(m_path))
		{}

		library(library&& other) :
		m_path(std::move(other.m_path)),
		m_lib(other.m_lib)
		{
			other.m_lib = LibraryTraits::default_value;
		}

		library& operator= (library other)
		{
			std::swap(*this, other);
			return *this;
		}

		~library()
		{
			LibraryTraits::release(m_lib);
		}

		template <typename Id>
		decltype(auto) operator[] (Id export_id)
		{
			static_assert(
				LibraryTraits::is_expected_idetifier(export_id),
				"Unexpected identifier");

			auto export_type = ExportMap::find_export(export_id);
			static_assert(
				!is_same<decltype(export_type), export_info<export_not_found>>::value,
				"Export not found.");

			return (export_type::type*)LibraryTraits::locate(m_lib, export_id::value);
		}

	private:
		path m_path;
		handle_t m_lib = LibraryTraits::default_handle;
	};
}
