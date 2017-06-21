#include "win32_library.hpp"

ddl::win32::traits::handle_t ddl::win32::traits::load(
	const std::experimental::filesystem::path & lib_path)
{
	const auto retVal = LoadLibraryW(lib_path.c_str());

	return retVal;
}

void ddl::win32::traits::release(handle_t lib)
{
	FreeLibrary(lib);
}