#include <cassert>
#include <cstring>

#include "decdynlib\decdynlib\exports_map.hpp"
#include "decdynlib\decdynlib\string_export.hpp"
#include "decdynlib\decdynlib\ordinal_export.hpp"

using ddl::type_t;
using ddl::export_info;
using ddl::export_not_found; 
using namespace ddl::literals;

void ordinal_exports_ids_tests()
{
	assert((ddl::export_id<ddl::ordinal_id<123>>{} == 123_eid));
	assert((123_eid == 123_eid));
	assert((321_eid != 123_eid));
	assert((decltype(123_eid)::value == 123));
}

void string_exports_ids_tests()
{
	assert((ddl::export_id<ddl::_ct_string<char, 'a','b','c'>>{} == "abc"_eid));
	assert(("abc"_eid == "abc"_eid));
	assert(("cba"_eid != "abc"_eid));
	assert((strcmp(decltype("abc"_eid)::value, "abc") == 0));
}

void exports_map_tests()
{
	auto map = make_exports_map(
		export_info<char>("char"_eid),
		export_info<char>(1_eid),
		export_info<int>("int"_eid),
		export_info<int>(3_eid)
	);

	assert((map.find_export(1_eid) == type_t<char>{}));
	assert((map.find_export(3_eid) == type_t<int>{}));
	assert((map.find_export("char"_eid) == type_t<char>{}));
	assert((map.find_export("int"_eid) == type_t<int>{}));
	assert((map.find_export(2_eid) == type_t<export_not_found>{}));
	assert((map.find_export("bla"_eid) == type_t<export_not_found>{}));
}

int main()
{
	ordinal_exports_ids_tests();
	string_exports_ids_tests();
	exports_map_tests();
}