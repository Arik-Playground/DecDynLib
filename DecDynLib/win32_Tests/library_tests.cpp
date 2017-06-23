#include <cassert>

#include "win32lib\library.hpp"

struct fake_export
{};

using namespace ddl::literals;

int main()
{
	auto g_kernel32_map = ddl::make_exports_map(
		ddl::export_info<decltype(::CreateFileW)>("CreateFileW"_eid),
		ddl::export_info<fake_export>(123_eid)
	);

	auto opt_kernel32 = ddl::win32::library(g_kernel32_map, "kernel32.dll");
	assert(opt_kernel32);
	auto& kernel32_ddl = *opt_kernel32;
	auto ordinal_export = kernel32_ddl[123_eid];
	assert(ordinal_export);
	auto create_file_string = kernel32_ddl["CreateFileW"_eid];
	assert(create_file_string);
	auto raw_kernel32 = LoadLibraryW(L"Kernel32.dll");
	auto raw_create_file = (decltype(&::CreateFileW))GetProcAddress(raw_kernel32, "CreateFileW");
	assert(create_file_string == raw_create_file);
	auto raw_ordinal_export = (fake_export*)GetProcAddress(raw_kernel32, (LPCSTR)123);
	assert(ordinal_export == raw_ordinal_export);
}