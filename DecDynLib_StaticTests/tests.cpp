/////////////////////////////////////////////////////////////////////////////////////////////
//
// Some simple tests, probably I should use a normal testing library in the future
//

#include <cassert>
#include <cinttypes>
#include <type_traits>

#include "decdynlib\decdynlib.hpp"

using ddl::export_t;
using ddl::export_info;
using ddl::make_export_map;
using ddl::export_not_found;
using namespace ddl::literals;

template <typename TLeft, typename TRight>
constexpr bool operator== (export_t<TLeft>, export_t<TRight>)
{
	return std::is_same<TLeft, TRight>::value;
}

void string_export_tests()
{
	auto map = make_export_map(
		export_info<char>("char"_eid),
		export_info<int>("int"_eid)
	);

	assert((map.find_export("char"_eid) == export_t<char>{}));
	assert((map.find_export("int"_eid) == export_t<int>{}));
	assert((map.find_export("bla"_eid) == export_t<export_not_found>{}));
}

void integer_export_tests()
{
	auto map = make_export_map(
		export_info<char>(1_eid),
		export_info<int>(3_eid)
	);

	assert((map.find_export(1_eid) == export_t<char>{}));
	assert((map.find_export(3_eid) == export_t<int>{}));
	assert((map.find_export("bla"_eid) == export_t<export_not_found>{}));
}

int main()
{
	string_export_tests();
	integer_export_tests();
}