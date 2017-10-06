#define CATCH_CONFIG_MAIN
#include <External\Catch\catch.hpp>

#include <Windows.h>

#include "win32lib\library.hpp"

#define TEST_MODULE_PATH L"kernel32.dll"

struct fake_export {};

using namespace ddl::literals;

constexpr static auto g_kernel32_map = ddl::make_exports_map(
	ddl::export_info<decltype(::CreateFileW)>("CreateFileW"_eid),
	ddl::export_info<fake_export>(123_eid));

TEST_CASE("Module creation test", "[Library]")
{
	SECTION("Invalid creation")
	{
		CHECK_FALSE(ddl::win32::load_library(g_kernel32_map, ""));
	}

	SECTION("Valid creation")
	{
		auto opt_kernel32 = ddl::win32::load_library(g_kernel32_map, TEST_MODULE_PATH);
		REQUIRE(opt_kernel32);
		auto& kernel32_ddl = *opt_kernel32;

		auto raw_kernel32 = LoadLibraryW(TEST_MODULE_PATH);
		CHECK(kernel32_ddl.get_raw_handle() == raw_kernel32);
	}
}

TEST_CASE("String exports tests", "[Exports]")
{
	auto opt_kernel32 = ddl::win32::load_library(g_kernel32_map, TEST_MODULE_PATH);
	auto& kernel32_ddl = *opt_kernel32;

	const auto ddl_export = kernel32_ddl["CreateFileW"_eid];
	CHECK(ddl_export);

	const auto raw_export = (decltype(CreateFileW)*)GetProcAddress(kernel32_ddl.get_raw_handle(), "CreateFileW");
	CHECK(ddl_export == raw_export);
}

TEST_CASE("Ordinal exports tests", "[Exports]")
{
	auto opt_kernel32 = ddl::win32::load_library(g_kernel32_map, TEST_MODULE_PATH);
	auto& kernel32_ddl = *opt_kernel32;

	const auto ddl_export = kernel32_ddl[123_eid];
	CHECK(ddl_export);

	const auto raw_export = (fake_export*)GetProcAddress(kernel32_ddl.get_raw_handle(), (LPCSTR)123);
	CHECK(ddl_export == raw_export);
}