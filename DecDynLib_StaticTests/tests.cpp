/////////////////////////////////////////////////////////////////////////////////////////////
//
// Some simple tests, probably I should use a normal testing library in the future
//

#include <string>
#include <cassert>
#include <cinttypes>
#include <type_traits>

#include "decdynlib\win32_library.hpp"
#include "decdynlib\decdynlib\string_export.hpp"
#include "decdynlib\decdynlib\ordinal_export.hpp"

using ddl::type_t;
using ddl::export_info;
using ddl::export_not_found;
using namespace ddl::literals;

void string_export_tests()
{
	auto map = make_export_map(
		export_info<char>("char"_eid),
		export_info<int>("int"_eid)
	);

	assert((map.find_export("char"_eid) == type_t<char>{}));
	assert((map.find_export("int"_eid) == type_t<int>{}));
	assert((map.find_export("bla"_eid) == type_t<export_not_found>{}));
}

void integer_export_tests()
{
	auto map = make_export_map(
		export_info<char>(1_eid),
		export_info<int>(3_eid)
	);

	assert((map.find_export(1_eid) == type_t<char>{}));
	assert((map.find_export(3_eid) == type_t<int>{}));
	assert((map.find_export(2_eid) == type_t<export_not_found>{}));
}

void mixed_export_tests()
{
	auto map = make_export_map(
		export_info<char>(1_eid),
		export_info<char>("char"_eid),
		export_info<int>(3_eid),
		export_info<int>("int"_eid)
	);

	assert((map.find_export(1_eid) == type_t<char>{}));
	assert((map.find_export(3_eid) == type_t<int>{}));
	assert((map.find_export("char"_eid) == type_t<char>{}));
	assert((map.find_export("int"_eid) == type_t<int>{}));
	assert((map.find_export(2_eid) == type_t<export_not_found>{}));
	assert((map.find_export("bla"_eid) == type_t<export_not_found>{}));
}

void library_test()
{
	struct fake_export {};

	auto map = make_export_map(
		export_info<fake_export>(130_eid),
		export_info<decltype(::CreateFileW)>("CreateFileW"_eid)
	);

	auto opt_dll = ddl::win32::library<decltype(map)>
		(std::experimental::filesystem::path(std::string("kernel32.dll")));
	assert(opt_dll);
	auto& dll = *opt_dll;
	auto ordinal_export = dll[130_eid];
	assert(ordinal_export);
	auto create_file_string = dll["CreateFileW"_eid];
	assert(create_file_string);
	auto raw_kernel32 = LoadLibraryW(L"Kernel32.dll");
	auto raw_create_file = (decltype(&::CreateFileW))GetProcAddress(raw_kernel32, "CreateFileW");
	assert(create_file_string == raw_create_file);
	auto raw_ordinal_export = (fake_export*)GetProcAddress(raw_kernel32, (LPCSTR)130);
	assert(ordinal_export == raw_ordinal_export);
}

int main()
{
	string_export_tests();
	integer_export_tests();
	mixed_export_tests();
	library_test();
}