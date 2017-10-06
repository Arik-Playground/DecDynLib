#define CATCH_CONFIG_MAIN
#include <External\Catch\catch.hpp>

#include "decdynlib\decdynlib\exports_map.hpp"
#include "decdynlib\decdynlib\string_export.hpp"
#include "decdynlib\decdynlib\ordinal_export.hpp"

using namespace std::string_literals;

using ddl::type_t;
using ddl::export_info;
using ddl::export_not_found; 
using namespace ddl::literals;

TEST_CASE("Ordinal export test","[export identifiers]")
{
	SECTION("Identifier creation")
	{
		CHECK((ddl::export_id<ddl::ordinal_id<123>>{} == 123_eid));
		CHECK((decltype(123_eid)::value == 123));
	}
	SECTION("Identifier comparison")
	{
		CHECK((123_eid == 123_eid));
		CHECK((321_eid != 123_eid));
	}
}

TEST_CASE("string export test", "[export identifiers]")
{
	SECTION("Identifier creation")
	{
		CHECK((ddl::export_id<ddl::_ct_string<char, 'a', 'b', 'c'>>{} == "abc"_eid));
		CHECK((decltype("abc"_eid)::value == "abc"s));
	}
	SECTION("Identifier comparison")
	{
		CHECK(("abc"_eid == "abc"_eid));
		CHECK(("cba"_eid != "abc"_eid));
	}
}

TEST_CASE("exports map test", "[exports map]")
{
	struct dummy_export_type
	{};

	auto map = make_exports_map(
		export_info<char>("char"_eid),
		export_info<char>(1_eid),
		export_info<int>("int"_eid),
		export_info<int>(3_eid),
		export_info<dummy_export_type>("dummy"_eid),
		export_info<dummy_export_type>(4_eid)
	);

	SECTION("ordinal export lookup")
	{
		CHECK((map.find_export(1_eid) == type_t<char>{}));
		CHECK((map.find_export(3_eid) == type_t<int>{}));
		CHECK((map.find_export(4_eid) == type_t<dummy_export_type>{}));
	}

	SECTION("string export lookup")
	{
		CHECK((map.find_export("char"_eid) == type_t<char>{}));
		CHECK((map.find_export("int"_eid) == type_t<int>{}));
		CHECK((map.find_export("dummy"_eid) == type_t<dummy_export_type>{}));
	}
	SECTION("non existing export lookup")
	{
		CHECK((map.find_export(2_eid) == type_t<export_not_found>{}));
		CHECK((map.find_export("bla"_eid) == type_t<export_not_found>{}));
	}
}