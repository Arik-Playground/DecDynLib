#pragma once

namespace ddl
{
	enum class os
	{
		Windows,
		Posix,
		Unknown
	};

	constexpr os os_type;
}

#ifdef _WIN32
#include <Windows.h>
ddl::os ddl::os_type = os::Windows;
#elif POSIX
#include <dlfcn.h>
ddl::os ddl::os_type = os::Posix;
#endif